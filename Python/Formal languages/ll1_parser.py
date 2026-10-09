import sys

EPS = "eps"


class Grammar:
    def __init__(self):
        self.nonterminals = set()
        self.terminals = set()
        self.start = None
        self.productions = {}  # idx -> (lhs, rhs_list)
        self.by_lhs = {}  # lhs -> list of (idx, rhs_list)

    @staticmethod
    def from_file(path):
        """
        Read grammar from file with format:
        NonTerminals: S A B ...
        Terminals: x y z ...
        Start: S
        Productions:
        S -> ...
        """
        g = Grammar()
        with open(path, "r") as f:
            lines = [line.strip() for line in f if line.strip() and not line.strip().startswith("#")]

        i = 0
        while i < len(lines):
            line = lines[i]
            if line.startswith("NonTerminals:"):
                parts = line.split(":", 1)[1].strip().split()
                g.nonterminals.update(parts)
            elif line.startswith("Terminals:"):
                parts = line.split(":", 1)[1].strip().split()
                g.terminals.update(parts)
            elif line.startswith("Start:"):
                g.start = line.split(":", 1)[1].strip()
            elif line.startswith("Productions:"):
                i += 1
                prod_index = 1
                while i < len(lines):
                    pline = lines[i]
                    if "->" not in pline:
                        i += 1
                        continue
                    lhs, rhs_part = pline.split("->")
                    lhs = lhs.strip()
                    alternatives = rhs_part.split("|")
                    for alt in alternatives:
                        rhs = alt.strip().split()
                        if len(rhs) == 1 and rhs[0] == EPS:
                            rhs = [EPS]
                        g.productions[prod_index] = (lhs, rhs)
                        g.by_lhs.setdefault(lhs, []).append((prod_index, rhs))
                        prod_index += 1
                    i += 1
                break
            i += 1

        return g


def compute_first(grammar):
    FIRST = {X: set() for X in grammar.nonterminals.union(grammar.terminals)}
    FIRST[EPS] = {EPS}

    for t in grammar.terminals:
        FIRST[t].add(t)

    changed = True
    while changed:
        changed = False
        for idx, (A, rhs) in grammar.productions.items():
            can_eps = True
            for Y in rhs:
                fy = FIRST.get(Y, set())
                for a in fy - {EPS}:
                    if a not in FIRST[A]:
                        FIRST[A].add(a)
                        changed = True
                if EPS not in fy:
                    can_eps = False
                    break
            if can_eps:
                if EPS not in FIRST[A]:
                    FIRST[A].add(EPS)
                    changed = True

    return FIRST


def first_of_string(symbols, FIRST):
    result = set()
    all_eps = True
    for Y in symbols:
        fy = FIRST.get(Y, set())
        result |= (fy - {EPS})
        if EPS not in fy:
            all_eps = False
            break
    if all_eps:
        result.add(EPS)
    return result


def compute_follow(grammar, FIRST):
    FOLLOW = {A: set() for A in grammar.nonterminals}
    FOLLOW[grammar.start].add("$")

    changed = True
    while changed:
        changed = False
        for idx, (B, rhs) in grammar.productions.items():
            for i, A in enumerate(rhs):
                if A in grammar.nonterminals:
                    beta = rhs[i + 1:]
                    if beta:
                        fb = first_of_string(beta, FIRST)
                        for a in fb - {EPS}:
                            if a not in FOLLOW[A]:
                                FOLLOW[A].add(a)
                                changed = True
                        if EPS in fb:
                            for b in FOLLOW[B]:
                                if b not in FOLLOW[A]:
                                    FOLLOW[A].add(b)
                                    changed = True
                    else:
                        for b in FOLLOW[B]:
                            if b not in FOLLOW[A]:
                                FOLLOW[A].add(b)
                                changed = True

    return FOLLOW


def build_table(grammar, FIRST, FOLLOW):
    table = {A: {} for A in grammar.nonterminals}
    conflicts = []

    for idx, (A, rhs) in grammar.productions.items():
        fa = first_of_string(rhs, FIRST)
        for a in fa - {EPS}:
            if a in table[A]:
                conflicts.append((A, a, table[A][a], idx))
            else:
                table[A][a] = idx

        if EPS in fa:
            for b in FOLLOW[A]:
                if b in table[A]:
                    conflicts.append((A, b, table[A][b], idx))
                else:
                    table[A][b] = idx

    return table, conflicts


def parse(tokens, grammar, table):
    """LL(1) parser - returns list of production indices"""
    stack = ["$", grammar.start]
    i = 0
    prod_sequence = []

    while stack:
        top = stack.pop()
        current = tokens[i]

        if top in grammar.terminals or top == "$":
            if top == current:
                i += 1
            else:
                raise Exception(f"Syntax error at position {i}: expected {top}, got {current}")
        elif top in grammar.nonterminals:
            A = top
            a = current
            if a not in table[A]:
                raise Exception(f"No rule for {A} with lookahead {a} at position {i}")

            prod_idx = table[A][a]
            prod_sequence.append(prod_idx)
            lhs, rhs = grammar.productions[prod_idx]

            if not (len(rhs) == 1 and rhs[0] == EPS):
                for s in reversed(rhs):
                    stack.append(s)
        else:
            raise Exception(f"Unknown symbol: {top}")

    if i != len(tokens):
        raise Exception(f"Input not fully consumed at position {i}")

    return prod_sequence


def main():
    if len(sys.argv) != 3:
        print("Usage: python .py <grammar_file> <input_file>")
        return

    grammar_file = sys.argv[1]
    input_file = sys.argv[2]

    # Parse grammar
    grammar = Grammar.from_file(grammar_file)

    # Compute FIRST and FOLLOW
    FIRST = compute_first(grammar)
    FOLLOW = compute_follow(grammar, FIRST)

    # Build LL(1) table
    table, conflicts = build_table(grammar, FIRST, FOLLOW)

    if conflicts:
        print("ERROR: Grammar is NOT LL(1). Conflicts found:")
        for (A, a, old_idx, new_idx) in conflicts:
            print(f"  M[{A}, {a}] has productions {old_idx} and {new_idx}")
        return
    else:
        print("Grammar is LL(1) - OK")

    # Read input tokens
    with open(input_file, "r") as f:
        content = f.read().strip()
        tokens = content.split()
        tokens.append("$")

    # Parse
    try:
        prod_seq = parse(tokens, grammar, table)
    except Exception as e:
        print(f"ERROR: {e}")
        return

    # Output production sequence
    print("Production sequence:")
    print(" ".join(str(p) for p in prod_seq))


if __name__ == "__main__":
    main()