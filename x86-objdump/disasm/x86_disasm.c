// src/disasm/x86_disasm.c
//
// Runtime/debug disassembler for the x86 VM.
//
// Phase 16 intentionally mirrors the proven decode/formatting rules used by
// x86-objdump, while keeping this module independent of the standalone tool.
// The shared architectural knowledge can be factored into a common decoder
// later; for now this eliminates the large trace-coverage gap without coupling
// libx86vm to a tool executable.

#include "disasm/x86_disasm.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    const uint8_t *data;
    size_t size;
    size_t pos;
    uint32_t origin;
} Reader;

typedef enum { SEG_NONE=-1, SEG_ES=0, SEG_CS=1, SEG_SS=2, SEG_DS=3 } Seg;

static const char *r8[8]  = {"al","cl","dl","bl","ah","ch","dh","bh"};
static const char *r16[8] = {"ax","cx","dx","bx","sp","bp","si","di"};
static const char *sreg[4]= {"es","cs","ss","ds"};

static int need(Reader *r, size_t n) { return r->pos + n <= r->size; }
static uint8_t rd8(Reader *r) { return r->data[r->pos++]; }
static uint16_t rd16(Reader *r) { uint16_t v=rd8(r); v|=(uint16_t)rd8(r)<<8; return v; }
static int8_t s8(uint8_t v){ return (int8_t)v; }
static int16_t s16(uint16_t v){ return (int16_t)v; }

static void fmt_addr(char *out,size_t n,uint32_t a){ snprintf(out,n,"0x%04X",(unsigned)(a&0xFFFF)); }

static int decode_ea16(Reader *r, uint8_t modrm, Seg seg, char *out, size_t n) {
    unsigned mod=(modrm>>6)&3, rm=modrm&7;
    if (mod==3) { snprintf(out,n,"%s",r16[rm]); return 1; }
    const char *base[8]={"bx+si","bx+di","bp+si","bp+di","si","di","bp","bx"};
    char inner[96]="";
    if (mod==0 && rm==6) {
        if(!need(r,2)) return 0;
        unsigned d=rd16(r);
        snprintf(inner,sizeof(inner),"0x%04X",d);
    } else {
        snprintf(inner,sizeof(inner),"%s",base[rm]);
        if(mod==1){
            if(!need(r,1)) return 0;
            int d=s8(rd8(r));
            if(d>0) snprintf(inner+strlen(inner),sizeof(inner)-strlen(inner),"+0x%X",d);
            else if(d<0) snprintf(inner+strlen(inner),sizeof(inner)-strlen(inner),"-0x%X",-d);
        } else if(mod==2){
            if(!need(r,2)) return 0;
            int d=s16(rd16(r));
            if(d>0) snprintf(inner+strlen(inner),sizeof(inner)-strlen(inner),"+0x%X",d);
            else if(d<0) snprintf(inner+strlen(inner),sizeof(inner)-strlen(inner),"-0x%X",-d);
        }
    }
    if(seg!=SEG_NONE) snprintf(out,n,"[%s:%s]",sreg[seg],inner);
    else snprintf(out,n,"[%s]",inner);
    return 1;
}

static int decode_one(Reader *r, char *text, size_t textn) {
    size_t start=r->pos;
    Seg seg=SEG_NONE;
    int rep=0;
    while(need(r,1)) {
        uint8_t p=r->data[r->pos];
        if(p==0x26){seg=SEG_ES;r->pos++;continue;}
        if(p==0x2E){seg=SEG_CS;r->pos++;continue;}
        if(p==0x36){seg=SEG_SS;r->pos++;continue;}
        if(p==0x3E){seg=SEG_DS;r->pos++;continue;}
        if(p==0xF2){rep=2;r->pos++;continue;}
        if(p==0xF3){rep=1;r->pos++;continue;}
        break;
    }
    if(!need(r,1)) { r->pos=start; return 0; }
    uint8_t op=rd8(r);
    char a[96], b[32];
    if(op>=0xB0 && op<=0xB7){ if(!need(r,1)) goto bad; snprintf(text,textn,"mov %s, 0x%02X",r8[op-0xB0],rd8(r)); return 1; }
    if(op>=0xB8 && op<=0xBF){ if(!need(r,2)) goto bad; snprintf(text,textn,"mov %s, 0x%04X",r16[op-0xB8],rd16(r)); return 1; }
    if(op>=0x40 && op<=0x47){ snprintf(text,textn,"inc %s",r16[op-0x40]); return 1; }
    if(op>=0x48 && op<=0x4F){ snprintf(text,textn,"dec %s",r16[op-0x48]); return 1; }
    if(op>=0x50 && op<=0x57){ snprintf(text,textn,"push %s",r16[op-0x50]); return 1; }
    if(op>=0x58 && op<=0x5F){ snprintf(text,textn,"pop %s",r16[op-0x58]); return 1; }
    if(op>=0x91 && op<=0x97){ snprintf(text,textn,"xchg ax, %s",r16[op-0x90]); return 1; }
    switch(op){
    case 0x06: snprintf(text,textn,"push es"); return 1;
    case 0x07: snprintf(text,textn,"pop es"); return 1;
    case 0x0E: snprintf(text,textn,"push cs"); return 1;
    case 0x16: snprintf(text,textn,"push ss"); return 1;
    case 0x17: snprintf(text,textn,"pop ss"); return 1;
    case 0x1E: snprintf(text,textn,"push ds"); return 1;
    case 0x1F: snprintf(text,textn,"pop ds"); return 1;
    case 0x90: snprintf(text,textn,"nop"); return 1;
    /* Immediate far control transfers encode offset first, then segment. */
    case 0x9A: {
        if (!need(r, 4)) goto bad;
        unsigned offset = rd16(r);
        unsigned segment = rd16(r);
        snprintf(text, textn, "call far 0x%04X:0x%04X", segment, offset);
        return 1;
    }
    case 0x98: snprintf(text,textn,"cbw"); return 1;
    case 0x99: snprintf(text,textn,"cwd"); return 1;
    case 0x9E: snprintf(text,textn,"sahf"); return 1;
    case 0x9F: snprintf(text,textn,"lahf"); return 1;
    case 0x9C: snprintf(text,textn,"pushf"); return 1;
    case 0x9D: snprintf(text,textn,"popf"); return 1;
    case 0xF4: snprintf(text,textn,"hlt"); return 1;
    case 0xFA: snprintf(text,textn,"cli"); return 1;
    case 0xFB: snprintf(text,textn,"sti"); return 1;
    case 0xFC: snprintf(text,textn,"cld"); return 1;
    case 0xFD: snprintf(text,textn,"std"); return 1;
    case 0xCF: snprintf(text,textn,"iret"); return 1;
    case 0xC2: if(!need(r,2)) goto bad; snprintf(text,textn,"ret 0x%X",rd16(r)); return 1;
    case 0xC3: snprintf(text,textn,"ret"); return 1;
    case 0xCA: if(!need(r,2)) goto bad; snprintf(text,textn,"retf 0x%X",rd16(r)); return 1;
    case 0xCB: snprintf(text,textn,"retf"); return 1;
    case 0xCD: if(!need(r,1)) goto bad; snprintf(text,textn,"int 0x%02X",rd8(r)); return 1;
    case 0x04: case 0x0C: case 0x14: case 0x1C: case 0x24: case 0x2C: case 0x34: case 0x3C: {
        if (!need(r, 1))
            goto bad;
        unsigned imm = rd8(r);
        const char *mn = op == 0x04 ? "add" :
                         op == 0x0C ? "or" :
                         op == 0x14 ? "adc" :
                         op == 0x1C ? "sbb" :
                         op == 0x24 ? "and" :
                         op == 0x2C ? "sub" :
                         op == 0x34 ? "xor" : "cmp";
        snprintf(text, textn, "%s al, 0x%02X", mn, imm);
        return 1;
    }
    case 0x05: case 0x0D: case 0x15: case 0x1D: case 0x25: case 0x2D: case 0x35: case 0x3D: {
        if (!need(r, 2))
            goto bad;
        unsigned imm = rd16(r);
        const char *mn = op == 0x05 ? "add" :
                         op == 0x0D ? "or" :
                         op == 0x15 ? "adc" :
                         op == 0x1D ? "sbb" :
                         op == 0x25 ? "and" :
                         op == 0x2D ? "sub" :
                         op == 0x35 ? "xor" : "cmp";
        snprintf(text, textn, "%s ax, 0x%04X", mn, imm);
        return 1;
    }
    case 0xA0: case 0xA1: case 0xA2: case 0xA3: { if(!need(r,2)) goto bad; unsigned off=rd16(r); const char *rn=(op==0xA0||op==0xA2)?"al":"ax"; if(seg!=SEG_NONE) snprintf(a,sizeof(a),"[%s:0x%04X]",sreg[seg],off); else snprintf(a,sizeof(a),"[0x%04X]",off); if(op==0xA0||op==0xA1) snprintf(text,textn,"mov %s, %s",rn,a); else snprintf(text,textn,"mov %s, %s",a,rn); return 1; }
    case 0xA8: if(!need(r,1)) goto bad; snprintf(text,textn,"test al, 0x%02X",rd8(r)); return 1;
    case 0xA9: if(!need(r,2)) goto bad; snprintf(text,textn,"test ax, 0x%04X",rd16(r)); return 1;
    case 0xE4: if(!need(r,1)) goto bad; snprintf(text,textn,"in al, 0x%02X",rd8(r)); return 1;
    case 0xE5: if(!need(r,1)) goto bad; snprintf(text,textn,"in ax, 0x%02X",rd8(r)); return 1;
    case 0xE6: if(!need(r,1)) goto bad; snprintf(text,textn,"out 0x%02X, al",rd8(r)); return 1;
    case 0xE7: if(!need(r,1)) goto bad; snprintf(text,textn,"out 0x%02X, ax",rd8(r)); return 1;
    case 0xEC: snprintf(text,textn,"in al, dx"); return 1;
    case 0xED: snprintf(text,textn,"in ax, dx"); return 1;
    case 0xEE: snprintf(text,textn,"out dx, al"); return 1;
    case 0xEF: snprintf(text,textn,"out dx, ax"); return 1;
    case 0xE0: case 0xE1: case 0xE2: { if(!need(r,1)) goto bad; int d=s8(rd8(r)); uint32_t t=r->origin+(uint32_t)r->pos+d; fmt_addr(a,sizeof(a),t); snprintf(text,textn,"%s %s",op==0xE0?"loopnz":op==0xE1?"loopz":"loop",a); return 1; }
    case 0xE3: { if(!need(r,1)) goto bad; int d=s8(rd8(r)); uint32_t t=r->origin+(uint32_t)r->pos+d; fmt_addr(a,sizeof(a),t); snprintf(text,textn,"jcxz %s",a); return 1; }
    case 0xE8: { if(!need(r,2)) goto bad; int d=s16(rd16(r)); uint32_t t=r->origin+(uint32_t)r->pos+d; fmt_addr(a,sizeof(a),t); snprintf(text,textn,"call %s",a); return 1; }
    case 0xE9: { if(!need(r,2)) goto bad; int d=s16(rd16(r)); uint32_t t=r->origin+(uint32_t)r->pos+d; fmt_addr(a,sizeof(a),t); snprintf(text,textn,"jmp %s",a); return 1; }
    case 0xEB: { if(!need(r,1)) goto bad; int d=s8(rd8(r)); uint32_t t=r->origin+(uint32_t)r->pos+d; fmt_addr(a,sizeof(a),t); snprintf(text,textn,"jmp short %s",a); return 1; }
    case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77:
    case 0x78: case 0x79: case 0x7A: case 0x7B: case 0x7C: case 0x7D: case 0x7E: case 0x7F: {
        static const char *mn[16]={"jo","jno","jb","jnb","jz","jnz","jbe","ja","js","jns","jp","jnp","jl","jge","jle","jg"};
        if(!need(r,1)) goto bad;
        int d=s8(rd8(r)); uint32_t t=r->origin+(uint32_t)r->pos+d;
        fmt_addr(a,sizeof(a),t); snprintf(text,textn,"%s %s",mn[op&15],a); return 1; }
    case 0xEA: { if(!need(r,4)) goto bad; unsigned off=rd16(r), sg=rd16(r); snprintf(text,textn,"jmp 0x%04X:0x%04X",sg,off); return 1; }
    case 0xC4: case 0xC5: { if(!need(r,1)) goto bad; uint8_t m=rd8(r); unsigned reg=(m>>3)&7,mod=(m>>6)&3; if(mod==3) goto unknown; if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad; snprintf(text,textn,"%s %s, %s",op==0xC4?"les":"lds",r16[reg],a); return 1; }
    case 0x00: case 0x02: case 0x10: case 0x12: case 0x18: case 0x1A: case 0x20: case 0x22: case 0x28: case 0x2A: case 0x38: case 0x3A: {
        if (!need(r, 1))
            goto bad;
        uint8_t m = rd8(r);
        unsigned reg = (m >> 3) & 7u;
        unsigned mod = (m >> 6) & 3u;
        unsigned rm = m & 7u;
        if(mod==3) snprintf(a,sizeof(a),"%s",r8[rm]); else if(!decode_ea16(r,m,seg,a,sizeof(a)))goto bad;
        unsigned fam=(op>>3)&7,rev=op&2; const char *mn=fam==0?"add":fam==2?"adc":fam==3?"sbb":fam==4?"and":fam==5?"sub":"cmp";
        if(rev)snprintf(text,textn,"%s %s, %s",mn,r8[reg],a);else snprintf(text,textn,"%s %s, %s",mn,a,r8[reg]);return 1; }
    case 0x30: case 0x32: {if(!need(r,1))goto bad;uint8_t m=rd8(r);unsigned reg=(m>>3)&7,mod=(m>>6)&3,rm=m&7;if(mod==3)snprintf(a,sizeof(a),"%s",r8[rm]);else if(!decode_ea16(r,m,seg,a,sizeof(a)))goto bad;if(op==0x32)snprintf(text,textn,"xor %s, %s",r8[reg],a);else snprintf(text,textn,"xor %s, %s",a,r8[reg]);return 1;}
    case 0x31: case 0x33: {if(!need(r,1))goto bad;uint8_t m=rd8(r);unsigned reg=(m>>3)&7,mod=(m>>6)&3,rm=m&7;if(mod==3)snprintf(a,sizeof(a),"%s",r16[rm]);else if(!decode_ea16(r,m,seg,a,sizeof(a)))goto bad;if(op==0x33)snprintf(text,textn,"xor %s, %s",r16[reg],a);else snprintf(text,textn,"xor %s, %s",a,r16[reg]);return 1;}
    case 0x0A: { if(!need(r,1)) goto bad; uint8_t m=rd8(r); unsigned reg=(m>>3)&7,mod=(m>>6)&3,rm=m&7; if(mod==3)snprintf(a,sizeof(a),"%s",r8[rm]);else if(!decode_ea16(r,m,seg,a,sizeof(a)))goto bad; snprintf(text,textn,"or %s, %s",r8[reg],a); return 1; }
    case 0x0B: { if(!need(r,1)) goto bad; uint8_t m=rd8(r); unsigned reg=(m>>3)&7; if(!decode_ea16(r,m,seg,a,sizeof(a)))goto bad; snprintf(text,textn,"or %s, %s",r16[reg],a); return 1; }
    case 0x84: case 0x86: case 0x08: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r); unsigned reg=(m>>3)&7,mod=(m>>6)&3,rm=m&7;
        if(mod==3) snprintf(a,sizeof(a),"%s",r8[rm]);
        else if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
        if(op==0x84) snprintf(text,textn,"test %s, %s",a,r8[reg]);
        else if(op==0x86) snprintf(text,textn,"xchg %s, %s",a,r8[reg]);
        else snprintf(text,textn,"or %s, %s",a,r8[reg]);
        return 1;
    }
    case 0x85: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r); unsigned reg=(m>>3)&7;
        if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
        snprintf(text,textn,"test %s, %s",a,r16[reg]);
        return 1;
    }
    case 0x87: { if(!need(r,1))goto bad; uint8_t m=rd8(r); unsigned reg=(m>>3)&7; if(!decode_ea16(r,m,seg,a,sizeof(a)))goto bad; snprintf(text,textn,"xchg %s, %s",a,r16[reg]); return 1; }
    case 0x8C: case 0x8E: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r); unsigned reg=(m>>3)&7,mod=(m>>6)&3;
        if(reg>3 || (op==0x8E && reg==1)) goto unknown;
        if(mod==3){if(op==0x8E)snprintf(text,textn,"mov %s, %s",sreg[reg],r16[m&7]);else snprintf(text,textn,"mov %s, %s",r16[m&7],sreg[reg]);}
        else {if(!decode_ea16(r,m,seg,a,sizeof(a)))goto bad;if(op==0x8E)snprintf(text,textn,"mov %s, %s",sreg[reg],a);else snprintf(text,textn,"mov %s, %s",a,sreg[reg]);} return 1; }
    case 0x01: case 0x03: case 0x11: case 0x13: case 0x19: case 0x1B: case 0x21: case 0x23: case 0x29: case 0x2B: case 0x39: case 0x3B: case 0x89: case 0x8B: case 0x8D: case 0x09: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r);
        unsigned reg=(m>>3)&7;
        if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
        snprintf(b,sizeof(b),"%s",r16[reg]);
        if(op==0x01) snprintf(text,textn,"add %s, %s",a,b);
        else if(op==0x03) snprintf(text,textn,"add %s, %s",b,a);
        else if(op==0x11) snprintf(text,textn,"adc %s, %s",a,b);
        else if(op==0x13) snprintf(text,textn,"adc %s, %s",b,a);
        else if(op==0x19) snprintf(text,textn,"sbb %s, %s",a,b);
        else if(op==0x1B) snprintf(text,textn,"sbb %s, %s",b,a);
        else if(op==0x21) snprintf(text,textn,"and %s, %s",a,b);
        else if(op==0x23) snprintf(text,textn,"and %s, %s",b,a);
        else if(op==0x29) snprintf(text,textn,"sub %s, %s",a,b);
        else if(op==0x2B) snprintf(text,textn,"sub %s, %s",b,a);
        else if(op==0x39) snprintf(text,textn,"cmp %s, %s",a,b);
        else if(op==0x3B) snprintf(text,textn,"cmp %s, %s",b,a);
        else if(op==0x89) snprintf(text,textn,"mov %s, %s",a,b);
        else if(op==0x8D) snprintf(text,textn,"lea %s, %s",b,a);
        else if(op==0x8B) snprintf(text,textn,"mov %s, %s",b,a);
        else if(op==0x31) snprintf(text,textn,"xor %s, %s",a,b);
        else snprintf(text,textn,"or %s, %s",a,b);
        return 1; }
    case 0x88: case 0x8A: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r); unsigned reg=(m>>3)&7, mod=(m>>6)&3, rm=m&7;
        if(mod==3) snprintf(a,sizeof(a),"%s",r8[rm]);
        else { if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad; }
        if(op==0x88) snprintf(text,textn,"mov %s, %s",a,r8[reg]); else snprintf(text,textn,"mov %s, %s",r8[reg],a);
        return 1; }
    case 0xC6: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r); if(((m>>3)&7)!=0)goto unknown;
        if(!decode_ea16(r,m,seg,a,sizeof(a))||!need(r,1))goto bad;
        unsigned imm=rd8(r);snprintf(text,textn,"mov byte %s, 0x%02X",a,imm);return 1; }
    case 0xC7: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r);
        if(((m>>3)&7)!=0) goto unknown;
        if(!decode_ea16(r,m,seg,a,sizeof(a)) || !need(r,2)) goto bad;
        unsigned imm=rd16(r); snprintf(text,textn,"mov word %s, 0x%04X",a,imm); return 1; }
    case 0x80: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r); unsigned ext=(m>>3)&7,mod=(m>>6)&3,rm=m&7;
        if(!(ext==0||ext==1||ext==2||ext==3||ext==4||ext==5||ext==7)) goto unknown;
        if(mod==3) snprintf(a,sizeof(a),"%s",r8[rm]);
        else if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
        if(!need(r,1)) goto bad;
        unsigned imm=rd8(r);
        snprintf(text,textn,"%s %s, 0x%X",ext==0?"add":ext==1?"or":ext==2?"adc":ext==3?"sbb":ext==4?"and":ext==5?"sub":"cmp",a,imm);
        return 1; }
    case 0x81: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r); unsigned ext=(m>>3)&7;
        if(!(ext==0||ext==1||ext==2||ext==3||ext==4||ext==5||ext==7)) goto unknown;
        if(!decode_ea16(r,m,seg,a,sizeof(a)) || !need(r,2)) goto bad;
        unsigned imm=rd16(r);
        snprintf(text,textn,"%s %s, 0x%04X",ext==0?"add":ext==1?"or":ext==2?"adc":ext==3?"sbb":ext==4?"and":ext==5?"sub":"cmp",a,imm);
        return 1; }
    case 0x8F: {if(!need(r,1))goto bad;uint8_t m=rd8(r);if(((m>>3)&7)!=0)goto unknown;if(!decode_ea16(r,m,seg,a,sizeof(a)))goto bad;snprintf(text,textn,"pop %s",a);return 1;}
    case 0xFE: {if(!need(r,1))goto bad;uint8_t m=rd8(r);unsigned ext=(m>>3)&7,mod=(m>>6)&3,rm=m&7;if(ext>1)goto unknown;if(mod==3)snprintf(a,sizeof(a),"%s",r8[rm]);else if(!decode_ea16(r,m,seg,a,sizeof(a)))goto bad;snprintf(text,textn,"%s %s",ext?"dec":"inc",a);return 1;}
    case 0xFF: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r); unsigned ext=(m>>3)&7,mod=(m>>6)&3,rm=m&7;

        if(ext==0 || ext==1){
            if(mod==3) snprintf(a,sizeof(a),"%s",r16[rm]);
            else if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
            snprintf(text,textn,"%s %s",ext?"dec":"inc",a);
            return 1;
        }

        if(ext==2){
            if(mod==3) snprintf(a,sizeof(a),"%s",r16[rm]);
            else if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
            snprintf(text,textn,"call %s",a);
            return 1;
        }

        if(ext==4){
            if(mod==3) snprintf(a,sizeof(a),"%s",r16[rm]);
            else if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
            snprintf(text,textn,"jmp %s",a);
            return 1;
        }

        if(ext==6){if(mod==3)snprintf(a,sizeof(a),"%s",r16[rm]);else if(!decode_ea16(r,m,seg,a,sizeof(a)))goto bad;snprintf(text,textn,"push %s",a);return 1;}

        if(ext==5 && mod!=3){
            if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
            snprintf(text,textn,"jmp far %s",a);
            return 1;
        }

        goto unknown; }
    case 0x83: {
        if(!need(r,2)) goto bad;
        uint8_t m=rd8(r);
        unsigned ext=(m>>3)&7;
        if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
        int imm=s8(rd8(r)); const char *mn=NULL;
        if(ext==0) mn="add"; else if(ext==1) mn="or"; else if(ext==2) mn="adc"; else if(ext==3) mn="sbb"; else if(ext==5) mn="sub"; else if(ext==7) mn="cmp"; else goto unknown;
        if(imm<0) snprintf(text,textn,"%s %s, byte -0x%X",mn,a,-imm); else snprintf(text,textn,"%s %s, byte 0x%X",mn,a,imm);
        return 1; }
    case 0xF6: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r); unsigned ext=(m>>3)&7,mod=(m>>6)&3,rm=m&7;
        if(ext!=0 && ext!=2 && ext!=3 && ext!=4 && ext!=6) goto unknown;
        if(mod==3) snprintf(a,sizeof(a),"%s",r8[rm]);
        else if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
        if(ext==0){if(!need(r,1))goto bad;snprintf(text,textn,"test %s, 0x%02X",a,rd8(r));return 1;}
        snprintf(text,textn,"%s %s",ext==2?"not":ext==3?"neg":ext==4?"mul":"div",a); return 1; }
    case 0xF7: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r); unsigned ext=(m>>3)&7;
        if(ext!=0 && ext!=2 && ext!=3 && ext!=4 && ext!=6) goto unknown;
        if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
        if(ext==0){if(!need(r,2))goto bad;snprintf(text,textn,"test %s, 0x%04X",a,rd16(r));return 1;}
        snprintf(text,textn,"%s %s",ext==2?"not":ext==3?"neg":ext==4?"mul":"div",a); return 1; }
    case 0xD0: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r); unsigned ext=(m>>3)&7,mod=(m>>6)&3,rm=m&7;
        if(ext!=1) goto unknown;
        if(mod==3) snprintf(a,sizeof(a),"%s",r8[rm]);
        else if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
        snprintf(text,textn,"ror %s, 1",a); return 1; }
    case 0xD1: case 0xD3: {
        if(!need(r,1)) goto bad;
        uint8_t m=rd8(r); unsigned ext=(m>>3)&7;
        if(ext!=4 && ext!=5) goto unknown;
        if(!decode_ea16(r,m,seg,a,sizeof(a))) goto bad;
        snprintf(text,textn,"%s %s, %s",ext==4?"shl":"shr",a,op==0xD1?"1":"cl"); return 1; }
    case 0xA4: snprintf(text,textn,"%smovsb",rep?"rep ":""); return 1;
    case 0xA5: snprintf(text,textn,"%smovsw",rep?"rep ":""); return 1;
    case 0xA6: snprintf(text,textn,"%scmpsb",rep==2?"repne ":rep?"repe ":""); return 1;
    case 0xA7: snprintf(text,textn,"%scmpsw",rep==2?"repne ":rep?"repe ":""); return 1;
    case 0xAE: snprintf(text,textn,"%sscasb",rep==2?"repne ":rep?"repe ":""); return 1;
    case 0xAF: snprintf(text,textn,"%sscasw",rep==2?"repne ":rep?"repe ":""); return 1;
    case 0xAC: snprintf(text,textn,"lodsb"); return 1;
    case 0xAD: snprintf(text,textn,"lodsw"); return 1;
    case 0xAA: snprintf(text,textn,"%sstosb",rep?"rep ":""); return 1;
    case 0xAB: snprintf(text,textn,"%sstosw",rep?"rep ":""); return 1;
    case 0xD7: snprintf(text,textn,"xlat"); return 1;
    case 0xF5: snprintf(text,textn,"cmc"); return 1;
    case 0xF8: snprintf(text,textn,"clc"); return 1;
    case 0xF9: snprintf(text,textn,"stc"); return 1;
    default: break;
    }
unknown:
    r->pos=start+1;
    snprintf(text,textn,"db 0x%02X",r->data[start]);
    return 1;
bad:
    r->pos=start+1;
    snprintf(text,textn,"db 0x%02X",r->data[start]);
    return 1;
}



static x86_disasm_t disasm_window(const uint8_t *bytes, size_t avail, uint32_t origin)
{
    x86_disasm_t d;
    Reader r;

    memset(&d, 0, sizeof(d));
    d.len = 1;
    d.ok = false;
    snprintf(d.text, sizeof(d.text), "db ?");

    if (!bytes || avail == 0) {
        snprintf(d.text, sizeof(d.text), "<no-bytes>");
        return d;
    }

    r.data = bytes;
    r.size = avail;
    r.pos = 0;
    r.origin = origin;

    if (!decode_one(&r, d.text, sizeof(d.text))) {
        snprintf(d.text, sizeof(d.text), "<trunc>");
        d.len = 1;
        return d;
    }

    d.len = r.pos ? r.pos : 1;
    d.ok = strncmp(d.text, "db 0x", 5) != 0;
    return d;
}

x86_disasm_t x86_disasm(const uint8_t *bytes, size_t avail)
{
    return disasm_window(bytes, avail, 0);
}

x86_disasm_t x86_disasm_at(const uint8_t *bytes, size_t avail, uint16_t ip)
{
    return disasm_window(bytes, avail, (uint32_t)ip);
}

x86_disasm_t x86_disasm_one_16(const uint8_t *mem, size_t memsz, uint32_t lin)
{
    if (!mem || lin >= memsz) {
        x86_disasm_t d;
        memset(&d, 0, sizeof(d));
        d.len = 1;
        snprintf(d.text, sizeof(d.text), "<oob>");
        return d;
    }

    /*
     * Back-compatible flat wrapper.  The low 16 bits are the best origin
     * available to this legacy API.  VM execution tracing uses x86_disasm_at()
     * directly with the architectural IP.
     */
    return disasm_window(mem + lin, memsz - (size_t)lin, (uint16_t)lin);
}
