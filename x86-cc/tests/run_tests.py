import os
import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
BUILD = HERE / "build"
CC = os.environ.get("X86_CC", str(ROOT / ("x86-cc.exe" if os.name == "nt" else "x86-cc")))
VM = os.environ.get("X86_RUN", "x86-run")

PHASES = [
    ("Blackjack C shell compiler regressions", [
        ("shell_compiler_regressions.c", "shell_compiler_regressions", 42),
        ("prefix_pointer_increment.c", "prefix_pointer_increment", 42),
    ]),
    ("Pipe compiler regressions", [
        ("pipe_struct_regression.c", "pipe_struct_regression", 42),
        ("pipe_literal_regression.c", "pipe_literal_regression", 42),
    ]),
    ("Frame scanner literal regressions", [
        ("frame_slots_escape_runtime.c", "frame_slots_escape_runtime", 42),
        ("frame_slots_typedef.c", "frame_slots_typedef", 42),
    ]),
    ("Phase 0 - Compiler Seed", [
        ("return42.c",            "return42",            42),
        ("add_constants.c",       "add_constants",       42),
    ]),
    ("Phase 1A - Additive Expressions", [
        ("sub_constants.c",       "sub_constants",       42),
        ("add_chain.c",           "add_chain",           42),
        ("sub_chain.c",           "sub_chain",           42),
        ("add_sub_chain.c",       "add_sub_chain",       42),
        ("parentheses.c",         "parentheses",         42),
        ("parentheses_group.c",   "parentheses_group",   38),
        ("parentheses_nested.c",  "parentheses_nested",  42),
        ("unary_plus.c",          "unary_plus",          42),
        ("unary_minus.c",         "unary_minus",         -1),
        ("unary_expression.c",    "unary_expression",    42),
        ("unary_bitwise_not.c",   "unary_bitwise_not",   42),
    ]),
    ("Phase 1B - Multiplicative Expressions and Precedence", [
        ("mul_constants.c",        "mul_constants",        42),
        ("div_constants.c",        "div_constants",        42),
        ("rem_constants.c",        "rem_constants",        42),
        ("mul_chain.c",            "mul_chain",            42),
        ("div_mul_chain.c",        "div_mul_chain",        42),
        ("precedence_mul_add.c",   "precedence_mul_add",   42),
        ("precedence_div_sub.c",   "precedence_div_sub",   42),
        ("parentheses_override.c", "parentheses_override", 42),
        ("mixed_nested.c",         "mixed_nested",         42),
        ("precedence_distinct.c",  "precedence_distinct",  14),
        ("parentheses_distinct.c", "parentheses_distinct", 20),
    ]),
    ("Phase 1C - Scalar Locals and Assignment", [
        ("local_decl_init.c",       "local_decl_init",       42),
        ("local_decl_assign.c",     "local_decl_assign",     42),
        ("local_reassign.c",        "local_reassign",        42),
        ("multiple_locals.c",       "multiple_locals",       42),
        ("local_add_constant.c",    "local_add_constant",    42),
        ("constant_add_local.c",    "constant_add_local",    42),
        ("local_sub_local.c",       "local_sub_local",       42),
        ("initializer_from_local.c", "initializer_from_local", 42),
        ("initializer_expression.c", "initializer_expression", 42),
        ("assignment_expression.c", "assignment_expression", 42),
        ("local_parentheses.c",     "local_parentheses",     42),
    ]),    ("Phase 1D - Runtime Multiplicative Integration", [
        ("runtime_mul_locals.c",       "runtime_mul_locals",       42),
        ("runtime_div_locals.c",       "runtime_div_locals",       42),
        ("runtime_rem_locals.c",       "runtime_rem_locals",       42),
        ("runtime_precedence.c",       "runtime_precedence",       14),
        ("runtime_parentheses.c",      "runtime_parentheses",      20),
        ("runtime_mul_chain.c",        "runtime_mul_chain",        42),
        ("runtime_div_mul_chain.c",    "runtime_div_mul_chain",    42),
        ("runtime_mixed_nested.c",     "runtime_mixed_nested",     42),
    ]),
    ("Phase 2A - Equality and Relational Expressions", [
        ("eq_true.c",                    "eq_true",                    1),
        ("eq_false.c",                   "eq_false",                   0),
        ("ne_true.c",                    "ne_true",                    1),
        ("ne_false.c",                   "ne_false",                   0),
        ("lt_true.c",                    "lt_true",                    1),
        ("lt_false.c",                   "lt_false",                   0),
        ("le_equal.c",                   "le_equal",                   1),
        ("gt_true.c",                    "gt_true",                    1),
        ("ge_equal.c",                   "ge_equal",                   1),
        ("compare_add_precedence.c",     "compare_add_precedence",     1),
        ("compare_mul_equality.c",       "compare_mul_equality",       1),
        ("runtime_lt_locals.c",          "runtime_lt_locals",          1),
        ("runtime_eq_locals.c",          "runtime_eq_locals",          1),
        ("runtime_gt_false.c",           "runtime_gt_false",           0),
        ("runtime_compare_precedence.c", "runtime_compare_precedence", 1),
        ("runtime_compare_mul_eq.c",     "runtime_compare_mul_eq",     1),
        ("runtime_signed_lt.c",          "runtime_signed_lt",          1),
    ]),
    ("Phase 2B - Compound Statements and if/else", [
        ("if_true.c",          "if_true",          42),
        ("if_false.c",         "if_false",         42),
        ("if_nonzero.c",       "if_nonzero",       42),
        ("if_zero.c",          "if_zero",          42),
        ("if_else_true.c",     "if_else_true",     42),
        ("if_else_false.c",    "if_else_false",    42),
        ("if_block.c",         "if_block",         42),
        ("if_else_blocks.c",   "if_else_blocks",   42),
        ("nested_if.c",        "nested_if",        42),
        ("dangling_else.c",    "dangling_else",    42),
    ]),
    ("Phase 2C - while, break, and continue", [
        ("while_count.c",             "while_count",             42),
        ("while_zero.c",              "while_zero",              42),
        ("while_nonzero.c",           "while_nonzero",           42),
        ("while_break.c",             "while_break",             42),
        ("while_continue.c",          "while_continue",          42),
        ("nested_while_break.c",      "nested_while_break",      42),
        ("nested_while_continue.c",   "nested_while_continue",   42),
    ]),
    ("Phase 2D - for loops", [
        ("for_count.c",               "for_count",               42),
        ("for_zero.c",                "for_zero",                42),
        ("for_break.c",               "for_break",               42),
        ("for_continue.c",            "for_continue",            42),
        ("nested_for_break.c",        "nested_for_break",        42),
        ("nested_for_continue.c",     "nested_for_continue",     42),
        ("mixed_for_while.c",         "mixed_for_while",         42),
    ]),
    ("Phase 2E - logical expressions and short-circuit evaluation", [
        ("logical_not.c",          "logical_not",          42),
        ("logical_double_not.c",   "logical_double_not",   42),
        ("logical_and_true.c",     "logical_and_true",     42),
        ("logical_and_false.c",    "logical_and_false",    42),
        ("logical_or_true.c",      "logical_or_true",      42),
        ("logical_or_false.c",     "logical_or_false",     42),
        ("logical_precedence.c",   "logical_precedence",   42),
        ("short_circuit_and.c",    "short_circuit_and",    42),
        ("short_circuit_or.c",     "short_circuit_or",     42),
        ("logical_loop.c",         "logical_loop",         42),
    ]),
    ("Phase 2F - lexical block scope and shadowing", [
        ("block_shadow.c",       "block_shadow",       42),
        ("nested_shadow.c",      "nested_shadow",      42),
        ("sibling_scope.c",      "sibling_scope",      42),
        ("outer_visible.c",      "outer_visible",      42),
        ("for_decl_scope.c",     "for_decl_scope",     42),
        ("for_shadow_outer.c",   "for_shadow_outer",   42),
    ]),
    ("Phase 3A - zero-argument functions and calls", [
        ("function_call.c", "function_call", 42),
        ("function_forward.c", "function_forward", 42),
        ("function_chain.c", "function_chain", 42),
        ("function_locals.c", "function_locals", 42),
    ]),
    ("Phase 3B - function parameters and arguments", [
        ("function_params.c", "function_params", 42),
        ("function_arg_expr.c", "function_arg_expr", 42),
        ("function_arg_locals.c", "function_arg_locals", 42),
        ("function_params_locals.c", "function_params_locals", 42),
        ("function_nested_calls.c", "function_nested_calls", 42),
        ("function_three_args.c", "function_three_args", 42),
    ]),
    ("Phase 3C - recursion and recursive frame composition", [
        ("recursive_sum.c", "recursive_sum", 42),
        ("recursive_locals.c", "recursive_locals", 42),
        ("recursive_depth.c", "recursive_depth", 42),
        ("mutual_recursion.c", "mutual_recursion", 42),
    ]),
    ("Phase 3D - function prototypes and signature validation", [
        ("function_prototype.c", "function_prototype", 42),
        ("function_unnamed_prototype.c", "function_unnamed_prototype", 42),
        ("function_repeated_prototype.c", "function_repeated_prototype", 42),
        ("function_prototype_recursion.c", "function_prototype_recursion", 42),
    ]),
    ("Phase 4A - pointers, address-of, and dereference", [
        ("pointer_read.c", "pointer_read", 42),
        ("pointer_write.c", "pointer_write", 42),
        ("pointer_retarget.c", "pointer_retarget", 42),
        ("pointer_expression.c", "pointer_expression", 42),
        ("pointer_assign_null.c", "pointer_assign_null", 42),
        ("unsigned_char_pointer.c", "unsigned_char_pointer", 42),
    ]),
    ("Phase 4B - explicit lvalues and rvalues", [
        ("lvalue_deref_address.c", "lvalue_deref_address", 42),
        ("lvalue_address_deref.c", "lvalue_address_deref", 42),
        ("lvalue_composed_store.c", "lvalue_composed_store", 42),
        ("lvalue_pointer_copy.c", "lvalue_pointer_copy", 42),
    ]),
    ("Phase 4C - pointer parameters across function boundaries", [
        ("pointer_param_read.c", "pointer_param_read", 42),
        ("pointer_param_write.c", "pointer_param_write", 42),
        ("pointer_param_copy.c", "pointer_param_copy", 42),
        ("pointer_param_recursive.c", "pointer_param_recursive", 42),
        ("pointer_param_prototype.c", "pointer_param_prototype", 42),
    ]),    ("Phase 4D - int arrays and indexed lvalues", [
        ("array_read.c", "array_read", 42),
        ("array_variable_index.c", "array_variable_index", 42),
        ("array_expression.c", "array_expression", 42),
        ("array_pass_pointer.c", "array_pass_pointer", 42),
        ("array_loop.c", "array_loop", 42),
    ]),
    ("Phase 4E - scaled int pointer arithmetic", [
        ("pointer_add.c", "pointer_add", 42),
        ("pointer_sub.c", "pointer_sub", 42),
        ("pointer_deref_arithmetic.c", "pointer_deref_arithmetic", 42),
        ("pointer_symmetric_add.c", "pointer_symmetric_add", 42),
        ("pointer_runtime_offset.c", "pointer_runtime_offset", 42),
    ]),
    ("Phase 4F - char objects, pointers, and byte arrays", [
        ("char_scalar.c", "char_scalar", 42),
        ("char_array.c", "char_array", 42),
        ("char_pointer.c", "char_pointer", 42),
        ("char_param.c", "char_param", 42),
        ("char_walk.c", "char_walk", 42),
    ]),
    ("Phase 4G - string literals and static data", [
        ("string_pointer.c", "string_pointer", 42),
        ("string_index.c", "string_index", 42),
        ("string_param.c", "string_param", 42),
        ("string_strlen.c", "string_strlen", 42),
        ("string_multiple.c", "string_multiple", 42),
    ]),
    ("Phase 4H - generalized pointer subscripting", [
        ("pointer_subscript_read.c", "pointer_subscript_read", 42),
        ("pointer_subscript_store.c", "pointer_subscript_store", 42),
        ("char_pointer_subscript.c", "char_pointer_subscript", 42),
        ("pointer_subscript_runtime.c", "pointer_subscript_runtime", 42),
        ("pointer_subscript_equivalence.c", "pointer_subscript_equivalence", 42),
    ]),
    ("Phase 4I - pointer depth and double pointers", [
        ("pointer_depth_int.c", "pointer_depth_int", 42),
        ("pointer_depth_store.c", "pointer_depth_store", 42),
        ("pointer_depth_param.c", "pointer_depth_param", 42),
        ("pointer_depth_char.c", "pointer_depth_char", 42),
        ("pointer_depth_subscript.c", "pointer_depth_subscript", 42),
    ]),
    ("Phase 4J - arrays of pointers", [
        ("pointer_array_int.c", "pointer_array_int", 42),
        ("pointer_array_char.c", "pointer_array_char", 42),
        ("pointer_array_decay.c", "pointer_array_decay", 42),
        ("pointer_array_runtime.c", "pointer_array_runtime", 42),
        ("pointer_array_store.c", "pointer_array_store", 42),
    ]),
    ("Phase 5A - struct objects and dot-member access", [
        ("struct_basic.c", "struct_basic", 42),
        ("struct_member_array.c", "struct_member_array", 42),
        ("struct_nested_union.c", "struct_nested_union", 42),
        ("struct_float_layout.c", "struct_float_layout", 42),
        ("struct_multi_declarator.c", "struct_multi_declarator", 42),
        ("struct_member_comments.c", "struct_member_comments", 42),
        ("struct_member_expression.c", "struct_member_expression", 42),
        ("struct_two_objects.c", "struct_two_objects", 42),
        ("struct_member_assignment.c", "struct_member_assignment", 42),
        ("struct_whole_assignment.c", "struct_whole_assignment", 42),
        ("struct_function_local.c", "struct_function_local", 42),
    ]),
    ("Phase 5B - struct pointers and arrow-member access", [
        ("struct_pointer_read.c", "struct_pointer_read", 42),
        ("struct_pointer_write.c", "struct_pointer_write", 42),
        ("struct_pointer_retarget.c", "struct_pointer_retarget", 42),
        ("struct_pointer_copy.c", "struct_pointer_copy", 42),
        ("struct_pointer_expression.c", "struct_pointer_expression", 42),
        ("struct_global_pointer_arrow.c", "struct_global_pointer_arrow", 42),
        ("struct_pointer_cast_constant.c", "struct_pointer_cast_constant", 42),
        ("struct_global_pointer_chain.c", "struct_global_pointer_chain", 42),
        ("struct_pointer_for_chain.c", "struct_pointer_for_chain", 42),
        ("struct_pointer_nested_chain.c", "struct_pointer_nested_chain", 42),
        ("nested_member_lvalue.c", "nested_member_lvalue", 42),
        ("secondary_struct_proto.c", "secondary_struct_proto", 42),
        ("struct_pointer_arithmetic.c", "struct_pointer_arithmetic", 42),
    ]),
    ("Phase 5C - typed struct members", [
        ("struct_typed_char.c", "struct_typed_char", 42),
        ("struct_typed_layout.c", "struct_typed_layout", 42),
        ("struct_pointer_member_int.c", "struct_pointer_member_int", 42),
        ("struct_pointer_member_char.c", "struct_pointer_member_char", 42),
        ("struct_typed_arrow.c", "struct_typed_arrow", 42),
    ]),
    ("Phase 5F - function pointers and ops tables", [
        ("function_pointer_struct_member.c", "function_pointer_struct_member", 42),
        ("function_pointer_ops_chain.c", "function_pointer_ops_chain", 42),
    ]),
    ("Phase 5E - struct member arrays and composed access", [
        ("struct_arrow_member_array_index.c", "struct_arrow_member_array_index", 42),
        ("struct_arrow_member_int_array_index.c", "struct_arrow_member_int_array_index", 42),
        ("struct_dot_member_array_index.c", "struct_dot_member_array_index", 42),
        ("struct_member_array_decay.c", "struct_member_array_decay", 42),
        ("struct_pointer_param_array.c", "struct_pointer_param_array", 42),
        ("body_comments.c", "body_comments", 42),
        ("large_struct_local.c", "large_struct_local", 42),
    ]),
    ("Phase 5D - real-program stress regressions", [
        ("large_local_array.c", "large_local_array", 42),
        ("string_hex_escape.c", "string_hex_escape", 42),
        ("long_if_body.c", "long_if_body", 42),
        ("long_while_body.c", "long_while_body", 42),
        ("long_for_body.c", "long_for_body", 42),
    ]),
    ("Phase 6A - declaration qualifiers", [
        ("qualifiers_static_const.c", "qualifiers_static_const", 42),
    ]),
    ("Phase 6B - global/static storage", [
        ("global_scalar.c", "global_scalar", 42),
        ("global_array.c", "global_array", 42),
        ("global_initialized.c", "global_initialized", 42),
        ("global_multiple.c", "global_multiple", 42),
        ("conditional_global_string.c", "conditional_global_string", 42),
    ]),
    ("Phase 6C - object macros and integer suffixes", [
        ("macro_array.c", "macro_array", 42),
        ("macro_expression.c", "macro_expression", 42),
    ]),
    ("Phase 6D - includes and named declaration types", [
        ("include_stdint_proto.c", "include_stdint_proto", 42),
        ("macro_lexical.c", "macro_lexical", 42),
        ("macro_function.c", "macro_function", 42),
        ("conditional_ifdef.c", "conditional_ifdef", 42),
        ("conditional_if.c", "conditional_if", 42),
        ("void_pointer_proto.c", "void_pointer_proto", 42),
        ("header_macro.c", "header_macro", 42),
        ("char_literal.c", "char_literal", 42),
    ]),
    ("Phase 6E - 32-bit scalar foundations", [
        ("wide_local_increment.c", "wide_local_increment", 42),
        ("wide_function_abi.c", "wide_function_abi", 42),
    ]),
    ("Phase 6F - vi language pressure", [
        ("vi_language_pressure.c", "vi_language_pressure", 42),
    ]),
    ("Phase 6G - coreutils language pressure", [
        ("coreutils_pressure_1.c", "coreutils_pressure_1", 13),
    ]),
    ("Phase 6H - independent corpus hardening", [
        ("null_statement.c", "null_statement", 0),
        ("adjacent_string_literals.c", "adjacent_string_literals", 42),
        ("macro_undef.c", "macro_undef", 42),
        ("function_pointer_return.c", "function_pointer_return", 42),
        ("void_pointer_return.c", "void_pointer_return", 42),
        ("sizeof_type.c", "sizeof_type", 42),
        ("global_postfix.c", "global_postfix", 42),
        ("variadic_abi.c", "variadic_abi", 42),
        ("variadic_ints.c", "variadic_ints", 42),
        ("variadic_stdarg.c", "variadic_stdarg", 42),
    ]),
    ("Phase 6I - include search and stdio ABI", [
        ("include_path.c", "include_path", 42),
        ("recursive_include.c", "recursive_include", 42),
    ]),
    ("Phase 6J - preprocessor and historical C pressure", [
        ("preproc_guarded_include.c", "preproc_guarded_include", 42),
        ("preproc_defined.c", "preproc_defined", 42),
        ("preproc_not_defined.c", "preproc_not_defined", 42),
        ("preproc_macro_include.c", "preproc_macro_include", 42),
        ("preproc_comment_include.c", "preproc_comment_include", 42),
        ("preproc_multiarg_macro.c", "preproc_multiarg_macro", 42),
        ("preproc_line_splice.c", "preproc_line_splice", 42),
        ("preproc_variadic_macro.c", "preproc_variadic_macro", 42),
        ("preproc_multiline_call.c", "preproc_multiline_call", 42),
        ("struct_long_alias.c", "struct_long_alias", 42),
        ("knr_function.c", "knr_function", 42),
        ("knr_pointer.c", "knr_pointer", 42),
    ]),
]

NEGATIVE_TESTS = [
    ("invalid_hex_escape.c", "invalid_hex_escape"),
    ("invalid_undeclared.c", "invalid_undeclared"),
    ("invalid_duplicate_local.c", "invalid_duplicate_local"),
    ("invalid_missing_rparen.c", "invalid_missing_rparen"),
    ("invalid_missing_semicolon.c", "invalid_missing_semicolon"),
    ("invalid_expression.c", "invalid_expression"),
    ("invalid_break_outside_loop.c", "invalid_break_outside_loop"),
    ("invalid_continue_outside_loop.c", "invalid_continue_outside_loop"),
    ("invalid_out_of_scope.c", "invalid_out_of_scope"),
    ("invalid_for_scope.c", "invalid_for_scope"),
    ("invalid_wrong_arity.c", "invalid_wrong_arity"),
    ("invalid_duplicate_parameter.c", "invalid_duplicate_parameter"),
    ("invalid_conflicting_prototype.c", "invalid_conflicting_prototype"),
    ("invalid_duplicate_function.c", "invalid_duplicate_function"),
    ("invalid_undefined_function.c", "invalid_undefined_function"),
    ("invalid_definition_missing_param_name.c", "invalid_definition_missing_param_name"),
    ("invalid_deref_nonpointer.c", "invalid_deref_nonpointer"),
    ("invalid_address_undeclared.c", "invalid_address_undeclared"),
    ("invalid_address_rvalue.c", "invalid_address_rvalue"),
    ("invalid_pointer_scalar_init.c", "invalid_pointer_scalar_init"),
    ("invalid_pointer_arg_scalar.c", "invalid_pointer_arg_scalar"),
    ("invalid_scalar_arg_pointer.c", "invalid_scalar_arg_pointer"),
    ("invalid_pointer_prototype_mismatch.c", "invalid_pointer_prototype_mismatch"),
    ("invalid_array_zero.c", "invalid_array_zero"),
    ("invalid_array_assignment.c", "invalid_array_assignment"),
    ("invalid_scalar_subscript.c", "invalid_scalar_subscript"),
    ("invalid_pointer_add_pointer.c", "invalid_pointer_add_pointer"),
    ("invalid_scalar_sub_pointer.c", "invalid_scalar_sub_pointer"),
    ("invalid_char_pointer_int_pointer.c", "invalid_char_pointer_int_pointer"),
    ("invalid_int_pointer_char_pointer.c", "invalid_int_pointer_char_pointer"),
    ("invalid_string_to_int_pointer.c", "invalid_string_to_int_pointer"),
    ("invalid_pointer_subscript_pointer.c", "invalid_pointer_subscript_pointer"),
    ("invalid_pointer_depth_base_mismatch.c", "invalid_pointer_depth_base_mismatch"),
    ("invalid_pointer_depth_arg.c", "invalid_pointer_depth_arg"),
    ("invalid_pointer_depth_three.c", "invalid_pointer_depth_three"),
    ("invalid_pointer_array_base_mismatch.c", "invalid_pointer_array_base_mismatch"),
    ("invalid_pointer_array_depth_three.c", "invalid_pointer_array_depth_three"),
    ("invalid_struct_unknown_type.c", "invalid_struct_unknown_type"),
    ("invalid_struct_unknown_member.c", "invalid_struct_unknown_member"),
    ("invalid_struct_duplicate_member.c", "invalid_struct_duplicate_member"),
    # Whole-struct assignment is valid C and is covered positively in Phase 5A.
    ("invalid_struct_pointer_mismatch.c", "invalid_struct_pointer_mismatch"),
    ("invalid_struct_arrow_object.c", "invalid_struct_arrow_object"),
    ("invalid_struct_dot_pointer.c", "invalid_struct_dot_pointer"),
    ("invalid_struct_pointer_depth_two.c", "invalid_struct_pointer_depth_two"),
    ("invalid_struct_member_pointer_mismatch.c", "invalid_struct_member_pointer_mismatch"),
    ("invalid_struct_member_char_pointer_mismatch.c", "invalid_struct_member_char_pointer_mismatch"),
    ("invalid_struct_member_pointer_depth_two.c", "invalid_struct_member_pointer_depth_two"),
]



NONTRIVIAL_BINARY_STEMS = {"shell_compiler_regressions", "prefix_pointer_increment", "pipe_struct_regression", "pipe_literal_regression", "frame_slots_escape_runtime", "frame_slots_typedef", "conditional_global_string", "global_scalar", "global_array", "global_initialized", "global_multiple", "macro_array", "include_stdint_proto", "macro_lexical", "void_pointer_proto", "char_literal", "wide_local_increment", "wide_function_abi", "vi_language_pressure", "coreutils_pressure_1", "null_statement", "adjacent_string_literals", "function_pointer_return", "void_pointer_return", "sizeof_type", "global_postfix", "variadic_abi", "variadic_ints", "variadic_stdarg", "include_path", "knr_function", "knr_pointer"}

STACK_BACKED_STEMS = {
    "frame_slots_escape_runtime", "frame_slots_typedef",
    "local_decl_init", "local_decl_assign", "local_reassign", "multiple_locals",
    "local_add_constant", "constant_add_local", "local_sub_local",
    "initializer_from_local", "initializer_expression", "assignment_expression",
    "local_parentheses", "unary_bitwise_not",
    "pointer_assign_null", "unsigned_char_pointer",
    "struct_whole_assignment", "nested_member_lvalue", "secondary_struct_proto",
    "runtime_mul_locals", "runtime_div_locals", "runtime_rem_locals",
    "runtime_precedence", "runtime_parentheses", "runtime_mul_chain",
    "runtime_div_mul_chain", "runtime_mixed_nested",
    "runtime_lt_locals", "runtime_eq_locals", "runtime_gt_false",
    "runtime_compare_precedence", "runtime_compare_mul_eq", "runtime_signed_lt",
    "if_true", "if_false", "if_nonzero", "if_zero", "if_else_true",
    "if_else_false", "if_block", "if_else_blocks", "nested_if", "dangling_else",
    "while_count", "while_zero", "while_nonzero", "while_break", "while_continue",
    "nested_while_break", "nested_while_continue",
    "for_count", "for_zero", "for_break", "for_continue",
    "nested_for_break", "nested_for_continue", "mixed_for_while",
    "logical_not", "logical_double_not", "logical_and_true", "logical_and_false",
    "logical_or_true", "logical_or_false", "logical_precedence",
    "short_circuit_and", "short_circuit_or", "logical_loop",
    "block_shadow", "nested_shadow", "sibling_scope", "outer_visible",
    "for_decl_scope", "for_shadow_outer",
    "function_call", "function_forward", "function_chain", "function_locals",
    "function_params", "function_arg_expr", "function_arg_locals",
    "function_pointer_struct_member", "function_pointer_ops_chain",
    "function_params_locals", "function_nested_calls", "function_three_args",
    "recursive_sum", "recursive_locals", "recursive_depth", "mutual_recursion",
    "function_prototype", "function_unnamed_prototype",
    "function_repeated_prototype", "function_prototype_recursion",
    "pointer_read", "pointer_write", "pointer_retarget", "pointer_expression",
    "lvalue_deref_address", "lvalue_address_deref", "lvalue_composed_store",
    "lvalue_pointer_copy",
    "pointer_param_read", "pointer_param_write", "pointer_param_copy",
    "pointer_param_recursive", "pointer_param_prototype",
    "array_read", "array_variable_index", "array_expression",
    "array_pass_pointer", "array_loop",
    "pointer_add", "pointer_sub", "pointer_deref_arithmetic",
    "char_scalar", "char_array", "char_pointer", "char_param", "char_walk",
    "string_pointer", "string_index", "string_param", "string_strlen", "string_multiple",
    "pointer_subscript_read", "pointer_subscript_store", "char_pointer_subscript",
    "pointer_subscript_runtime", "pointer_subscript_equivalence",
    "pointer_depth_int", "pointer_depth_store", "pointer_depth_param",
    "pointer_depth_char", "pointer_depth_subscript",
    "pointer_array_int", "pointer_array_char", "pointer_array_decay",
    "pointer_array_runtime", "pointer_array_store",
    "struct_basic", "struct_member_array", "struct_nested_union", "struct_float_layout",
    "struct_multi_declarator", "struct_member_comments", "struct_member_expression", "struct_two_objects",
    "struct_member_assignment", "struct_function_local",
    "struct_pointer_read", "struct_pointer_write", "struct_pointer_retarget",
    "struct_pointer_copy", "struct_pointer_expression",
    "struct_global_pointer_arrow", "struct_pointer_cast_constant", "struct_global_pointer_chain", "struct_pointer_for_chain", "struct_pointer_nested_chain", "struct_pointer_arithmetic",
    "struct_typed_char", "struct_typed_layout", "struct_pointer_member_int",
    "struct_pointer_member_char", "struct_typed_arrow",
    "struct_arrow_member_array_index", "struct_arrow_member_int_array_index",
    "struct_dot_member_array_index", "struct_member_array_decay", "struct_pointer_param_array",
    "body_comments", "large_struct_local",
    "pointer_symmetric_add", "pointer_runtime_offset",
    "large_local_array", "string_hex_escape", "long_if_body", "long_while_body", "long_for_body",
    "qualifiers_static_const",
}

SKIP_EXACT_ASM_STEMS = {"include_stdint_proto", "macro_lexical", "global_initialized", "global_multiple", "void_pointer_proto", "wide_local_increment", "wide_function_abi", "vi_language_pressure", "coreutils_pressure_1", "null_statement", "adjacent_string_literals", "function_pointer_return", "void_pointer_return", "sizeof_type", "global_postfix", "variadic_abi", "variadic_ints", "variadic_stdarg", "include_path", "knr_function", "knr_pointer"}


def run(cmd, cwd=HERE, input_text=None, env=None):
    return subprocess.run(cmd, cwd=cwd, input=input_text, text=True,
                          stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                          env=env)


def check(label, condition, detail=""):
    if condition:
        print(f"  PASS {label}")
        return True
    print(f"  FAIL {label}")
    if detail:
        print(f"       {detail}")
    return False


def u16(value):
    return value & 0xFFFF


def expected_asm(value):
    return f"mov ax, 0x{u16(value):04X}"


def expected_binary(value):
    v = u16(value)
    return bytes((0xB8, v & 0xFF, (v >> 8) & 0xFF, 0xF4))


def vm_available():
    if os.path.isabs(VM) or os.sep in VM or (os.altsep and os.altsep in VM):
        return Path(VM).exists()
    return shutil.which(VM) is not None


def compile_and_run(src_name, stem, expected):
    ok = True
    src = HERE / src_name
    binary = BUILD / f"{stem}.bin"
    log = BUILD / f"{stem}.log"
    asm = BUILD / f"{stem}.asm"

    cc_extra = ["-I", str(HERE / "include")] if stem in {"include_path", "recursive_include", "preproc_guarded_include", "preproc_macro_include"} else []
    p = run([CC] + cc_extra + ["-S", str(src), "-o", str(asm)])
    ok &= check(f"{stem} -S", p.returncode == 0, p.stdout)
    if p.returncode == 0:
        text = asm.read_text()
        if stem in STACK_BACKED_STEMS:
            checks = ["push bp", "mov bp, sp", "mov sp, bp", "pop bp", "hlt"]
            ok &= check(f"{stem} stack-backed assembly",
                        all(want in text for want in checks), text)
            if stem.startswith("function_") or stem.startswith("pointer_param_") or stem in {"recursive_sum", "recursive_locals",
                                                          "recursive_depth", "mutual_recursion",
                                                          "function_prototype", "function_unnamed_prototype",
                                                          "function_repeated_prototype", "function_prototype_recursion"}:
                ok &= check(f"{stem} function call code",
                            "call main" in text and "ret" in text and "call " in text, text)
                if stem in {"function_params", "function_arg_expr", "function_arg_locals",
                            "function_params_locals", "function_nested_calls", "function_three_args",
                            "recursive_sum", "recursive_locals", "recursive_depth", "mutual_recursion",
                            "function_prototype", "function_unnamed_prototype",
                            "function_repeated_prototype", "function_prototype_recursion",
                            "pointer_param_read", "pointer_param_write", "pointer_param_copy",
                            "pointer_param_recursive", "pointer_param_prototype"}:
                    ok &= check(f"{stem} parameter/argument code",
                                "[bp+" in text and "push ax" in text and "pop bx" in text, text)
                if stem.startswith("function_pointer_"):
                    ok &= check(f"{stem} indirect function call code",
                                "call si" in text and "mov si, [bx]" in text, text)
                if stem.startswith("pointer_param_"):
                    ok &= check(f"{stem} pointer parameter code",
                                "[bp+" in text and ("mov ax, [bx]" in text or "mov [bx], ax" in text), text)
                if stem in {"recursive_sum", "recursive_locals", "recursive_depth", "mutual_recursion"}:
                    ok &= check(f"{stem} recursive call code",
                                ("call sum" in text or "call sum_local" in text or
                                 "call climb" in text or
                                 ("call is_even" in text and "call is_odd" in text)), text)
            elif stem.startswith("array_"):
                ok &= check(f"{stem} array/index code",
                            "add ax, ax" in text and "mov ax, bp" in text, text)
                if stem == "array_pass_pointer":
                    ok &= check(f"{stem} array decay/call code",
                                "call first" in text and "push ax" in text, text)
            elif stem in {"pointer_add", "pointer_sub", "pointer_deref_arithmetic",
                          "pointer_symmetric_add", "pointer_runtime_offset"}:
                ok &= check(f"{stem} scaled pointer arithmetic code",
                            ("add ax, ax" in text or "add bx, bx" in text) and
                            ("add bx, ax" in text or "sub bx, ax" in text or "add ax, bx" in text), text)
            elif stem in {"pointer_read", "pointer_write", "pointer_retarget", "pointer_expression",
                          "lvalue_deref_address", "lvalue_address_deref",
                          "lvalue_composed_store", "lvalue_pointer_copy"}:
                ok &= check(f"{stem} pointer/lvalue code",
                            "mov ax, bp" in text and
                            ("mov ax, [bx]" in text or "mov [bx], ax" in text), text)
                if stem in {"pointer_write", "lvalue_composed_store", "lvalue_pointer_copy"}:
                    ok &= check(f"{stem} indirect store", "mov [bx], ax" in text, text)
            elif stem in {"pointer_subscript_read", "pointer_subscript_store", "char_pointer_subscript",
                          "pointer_subscript_runtime", "pointer_subscript_equivalence"}:
                ok &= check(f"{stem} pointer subscript code",
                            "pop bx" in text and "add ax, bx" in text and
                            ("mov ax, [bx]" in text or "mov al, [bx]" in text or "mov [bx], ax" in text), text)
                if stem in {"pointer_subscript_read", "pointer_subscript_store"}:
                    ok &= check(f"{stem} pointer subscript call code", "call " in text and "[bp+" in text, text)
                if stem != "char_pointer_subscript":
                    ok &= check(f"{stem} int index scaling", "add ax, ax" in text, text)
            elif stem in {"pointer_array_int", "pointer_array_char", "pointer_array_decay",
                          "pointer_array_runtime", "pointer_array_store"}:
                ok &= check(f"{stem} pointer-array code",
                            "add ax, ax" in text and
                            ("mov [bx], ax" in text or "mov ax, [bx]" in text), text)
                if stem in {"pointer_array_decay", "pointer_array_runtime"}:
                    ok &= check(f"{stem} array decay/call code", "call " in text and "push ax" in text, text)
                if stem == "pointer_array_char":
                    ok &= check(f"{stem} string pointer elements", ".Lstr_" in text and "db " in text, text)
            elif stem in {"struct_basic", "struct_member_expression", "struct_two_objects",
                          "struct_member_assignment", "struct_function_local"}:
                ok &= check(f"{stem} struct/member code",
                            "mov ax, bp" in text and "mov [bx], ax" in text and "mov ax, [bx]" in text, text)
                if stem in {"struct_basic", "struct_member_expression", "struct_two_objects",
                            "struct_member_assignment", "struct_function_local"}:
                    ok &= check(f"{stem} member offset code",
                                ("add ax, 2" in text or ("mov bx, 2" in text and "add ax, bx" in text)), text)
                if stem == "struct_function_local":
                    ok &= check(f"{stem} function integration", "call build" in text and "ret" in text, text)
            elif stem in {"struct_pointer_read", "struct_pointer_write", "struct_pointer_retarget",
                          "struct_pointer_copy", "struct_pointer_expression"}:
                ok &= check(f"{stem} struct-pointer/arrow code",
                            "mov ax, bp" in text and "mov ax, [bp-" in text and
                            ("mov [bx], ax" in text or "mov ax, [bx]" in text), text)
                ok &= check(f"{stem} arrow member offset code",
                            ("add ax, 2" in text or ("mov bx, 2" in text and "add ax, bx" in text)), text)
            elif stem in {"struct_typed_char", "struct_typed_layout", "struct_pointer_member_int",
                          "struct_pointer_member_char", "struct_typed_arrow"}:
                ok &= check(f"{stem} typed struct-member code",
                            "mov ax, bp" in text and
                            ("mov [bx], al" in text or "mov [bx], ax" in text) and
                            ("mov al, [bx]" in text or "mov ax, [bx]" in text), text)
                if stem in {"struct_typed_char", "struct_typed_arrow"}:
                    ok &= check(f"{stem} byte member code",
                                "mov [bx], al" in text and "mov al, [bx]" in text, text)
                if stem == "struct_typed_layout":
                    ok &= check(f"{stem} packed member offset",
                                ("add ax, 1" in text or ("mov bx, 1" in text and "add ax, bx" in text)), text)
                if stem in {"struct_pointer_member_int", "struct_pointer_member_char"}:
                    ok &= check(f"{stem} pointer member code",
                                "mov [bx], ax" in text and "mov ax, [bx]" in text, text)
                if stem == "struct_pointer_member_char":
                    ok &= check(f"{stem} char pointee code", "mov al, [bx]" in text, text)
            elif stem in {"struct_arrow_member_array_index", "struct_arrow_member_int_array_index",
                          "struct_dot_member_array_index", "struct_member_array_decay",
                          "struct_pointer_param_array", "body_comments", "large_struct_local",
                          "struct_member_array", "struct_nested_union", "struct_float_layout",
                          "struct_multi_declarator", "struct_member_comments",
                          "struct_whole_assignment", "secondary_struct_proto"}:
                ok &= check(f"{stem} Phase 5E composed code", "mov ax" in text and "ret" in text, text)
                if stem in {"struct_arrow_member_array_index", "struct_arrow_member_int_array_index",
                            "struct_dot_member_array_index", "struct_pointer_param_array"}:
                    ok &= check(f"{stem} member-array addressing", "add ax, bx" in text, text)
            elif stem in {"struct_global_pointer_arrow", "struct_global_pointer_chain"}:
                ok &= check(f"{stem} global struct-pointer code",
                            ".G_" in text and "mov [bx], ax" in text and "mov ax, [bx]" in text, text)
            elif stem in {"pointer_depth_int", "pointer_depth_store", "pointer_depth_param",
                          "pointer_depth_char", "pointer_depth_subscript"}:
                ok &= check(f"{stem} double-pointer code",
                            "mov ax, bp" in text and "mov ax, [bx]" in text, text)
                if stem == "pointer_depth_store":
                    ok &= check(f"{stem} double-deref store", "mov [bx], ax" in text, text)
                if stem == "pointer_depth_param":
                    ok &= check(f"{stem} double-pointer call code", "call read" in text and "[bp+" in text, text)
                if stem == "pointer_depth_char":
                    ok &= check(f"{stem} char double-deref code", "mov al, [bx]" in text, text)
                if stem == "pointer_depth_subscript":
                    ok &= check(f"{stem} pointer-sized index scaling", "add ax, ax" in text, text)
            elif stem in {"string_pointer", "string_index", "string_param", "string_strlen", "string_multiple"}:
                ok &= check(f"{stem} string/static-data code",
                            ".Lstr_" in text and "db " in text and "0x00" in text, text)
                if stem in {"string_param", "string_strlen", "string_multiple"}:
                    ok &= check(f"{stem} string call code", "call " in text and "push ax" in text, text)
                if stem == "string_strlen":
                    ok &= check(f"{stem} long literal chunking", text.count("    db ") >= 3, text)
            elif stem in {"char_scalar", "char_array", "char_pointer", "char_param", "char_walk"}:
                ok &= check(f"{stem} byte object code",
                            ("mov al, [" in text or "mov [bx], al" in text or "mov [bp-" in text), text)
            elif stem == "large_local_array":
                ok &= check(f"{stem} 512-byte frame addressing",
                            ("mov bx, 512" in text or "sub ax, 512" in text) and "mov [bx], al" in text and "mov al, [bx]" in text, text)
            elif stem in SKIP_EXACT_ASM_STEMS:
                ok &= check(f"{stem} named-type call code", "call .F_take" in text and "push ax" in text, text)
            else:
                ok &= check(f"{stem} local load/store",
                            "[bp-" in text and ("mov [bp-" in text or "mov [bx], ax" in text), text)
            if stem in {"runtime_mul_locals", "runtime_div_locals", "runtime_rem_locals",
                        "runtime_precedence", "runtime_parentheses", "runtime_mul_chain",
                        "runtime_div_mul_chain", "runtime_mixed_nested"}:
                ok &= check(f"{stem} runtime multiplicative code",
                            any(op in text for op in ("mul bx", "div bx")), text)
            if stem in {"runtime_lt_locals", "runtime_eq_locals", "runtime_gt_false",
                        "runtime_compare_precedence", "runtime_compare_mul_eq", "runtime_signed_lt"}:
                ok &= check(f"{stem} runtime comparison code",
                            "cmp ax, bx" in text and ".Lcmp_end_" in text, text)
            if stem in {"while_count", "while_zero", "while_nonzero", "while_break",
                        "while_continue", "nested_while_break", "nested_while_continue"}:
                ok &= check(f"{stem} loop control-flow code",
                            ".Lwhile_cond_" in text and ".Lwhile_end_" in text, text)
            if stem in {"for_count", "for_zero", "for_break", "for_continue",
                        "nested_for_break", "nested_for_continue", "mixed_for_while"}:
                ok &= check(f"{stem} for control-flow code",
                            ".Lfor_cond_" in text and ".Lfor_continue_" in text and
                            ".Lfor_end_" in text, text)
            if stem in {"logical_not", "logical_double_not", "logical_and_true",
                        "logical_and_false", "logical_or_true", "logical_or_false",
                        "logical_precedence", "short_circuit_and", "short_circuit_or",
                        "logical_loop"}:
                ok &= check(f"{stem} logical code",
                            "cmp ax, 0" in text and
                            any(mark in text for mark in (".Lnot_end_", ".Land_", ".Lor_")), text)
            if stem in {"if_true", "if_false", "if_nonzero", "if_zero",
                        "if_else_true", "if_else_false", "if_block",
                        "if_else_blocks", "nested_if", "dangling_else"}:
                ok &= check(f"{stem} control-flow code",
                            "cmp ax, 0" in text and ".Lif_else_" in text and
                            "jmp .Lreturn" in text, text)
        elif stem not in SKIP_EXACT_ASM_STEMS:
            want = expected_asm(expected)
            ok &= check(f"{stem} assembly result", want in text,
                        f"expected {want!r}\n{text}")

    p = run([CC] + cc_extra + [str(src), "-o", str(binary)])
    ok &= check(f"{stem} compile", p.returncode == 0, p.stdout)
    if p.returncode != 0:
        return ok

    data = binary.read_bytes()
    if stem in STACK_BACKED_STEMS or stem in NONTRIVIAL_BINARY_STEMS:
        ok &= check(f"{stem} binary produced", len(data) > 4,
                    f"expected stack-backed program, got {data.hex(' ')}")
    else:
        want_bytes = expected_binary(expected)
        ok &= check(f"{stem} binary bytes", data == want_bytes,
                    f"expected {want_bytes.hex(' ')} got {data.hex(' ')}")

    if vm_available():
        script = (HERE / "test.script.in").read_text()
        script = script.replace("@LOG@", str(log)).replace("@BIN@", str(binary))
        p = run([VM], input_text=script)
        ok &= check(f"{stem} VM run", p.returncode == 0, p.stdout)
        if log.exists():
            text = log.read_text()
            ax = f"AX={u16(expected):04X}"
            ok &= check(f"{stem} {ax}", ax in text, text)
            ok &= check(f"{stem} HLT", "hlt" in text.lower(), text)
        else:
            ok &= check(f"{stem} log produced", False)
    else:
        print(f"  SKIP {stem} VM run (x86-run not found)")

    return ok


def main():
    print("Running x86-cc 0.0.56 tests...")
    shutil.rmtree(BUILD, ignore_errors=True)
    BUILD.mkdir(parents=True)

    ok = True
    p = run([CC, "--version"])
    ok &= check("version", p.returncode == 0 and "x86-cc 0.0.56" in p.stdout, p.stdout)

    tu_asm = BUILD / "translation_unit.asm"
    p = run([CC, "-S", str(HERE / "translation_unit.c"), "-o", str(tu_asm)])
    tu_text = tu_asm.read_text() if p.returncode == 0 and tu_asm.exists() else ""
    ok &= check("translation-unit -S without main",
                p.returncode == 0 and "add_one:" in tu_text and "_start:" not in tu_text,
                p.stdout + tu_text)

    # Compile-only cases: external libc calls are intentionally unresolved here.
    for name in ("frame_slots_ping_regression.c", "frame_slots_string_keywords.c",
                 "frame_slots_escaped_literals.c"):
        obj = BUILD / (Path(name).stem + ".o")
        p = run([CC, "-c", "--blackjack", str(HERE / name), "-o", str(obj)])
        ok &= check(f"{name} compiles", p.returncode == 0, p.stdout)

    for phase_name, tests in PHASES:
        print()
        print(phase_name)
        print("-" * 72)
        for src_name, stem, expected in tests:
            ok &= compile_and_run(src_name, stem, expected)

    print()
    print("Diagnostics")
    print("-" * 72)
    for src_name, stem in NEGATIVE_TESTS:
        src = HERE / src_name
        asm = BUILD / f"{stem}.asm"
        p = run([CC, "-S", str(src), "-o", str(asm)])
        ok &= check(f"{stem} rejected", p.returncode != 0, p.stdout)

    print(f"x86-cc: {'PASS' if ok else 'FAIL'}")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
