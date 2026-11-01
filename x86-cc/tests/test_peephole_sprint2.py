from peephole_sprint2 import optimize

cases = [
    ('mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\ncmp ax, 0\n', 2),
    ('mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\njz somewhere\n', 0),
    ('mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\n.L1:\ncmp ax, 0\n', 0),
    ('mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\ncall func\ncmp ax, 0\n', 0),
    ('mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\npush ax\ncmp ax, 0\n', 2),
    ('mov ax, bp\nsub ax, 2\nmov ax, [bp-2]\n; comment\nadd bx, ax\n', 2),
]
for source, expected in cases:
    result, removed = optimize(source)
    assert removed == expected, (source, removed, expected)
    if expected:
        assert result.startswith('mov ax, [bp-2]\n')
    else:
        assert result == source
print('PASS peephole safety and elimination cases:', len(cases))
