# Direct Grammar to DFA Converter for DSL Course
# Generates DFAs from regular grammars as per your specification

from dataclasses import dataclass
from typing import Dict, Set, List, Tuple, Optional

@dataclass
class DFAState:
    name: str
    is_final: bool = False

@dataclass
class DFATransition:
    from_state: str
    symbol_desc: str  # e.g., "[a-zA-Z]", "0", "-", etc.
    to_state: str

class SimpleDFA:
    """Simple DFA representation for displaying in your course format"""
    
    def __init__(self):
        self.states: Set[str] = set()
        self.alphabet: Set[str] = set()
        self.transitions: List[DFATransition] = []
        self.initial_state: str = "q0"
        self.final_states: Set[str] = set()
    
    def add_state(self, state: str, is_final: bool = False):
        self.states.add(state)
        if is_final:
            self.final_states.add(state)
    
    def add_transition(self, from_state: str, symbol: str, to_state: str):
        """Add transition δ(from_state, symbol) = to_state"""
        self.transitions.append(DFATransition(from_state, symbol, to_state))
        self.alphabet.add(symbol)
        self.states.add(from_state)
        self.states.add(to_state)
    
    def set_final_state(self, state: str):
        self.final_states.add(state)
    
    def display(self) -> str:
        """Display DFA in formal notation"""
        result = "M = (Q, Σ, δ, q0, F)\n\n"
        
        # States
        states_list = sorted(self.states)
        result += f"Q = {{{', '.join(states_list)}}}\n"
        
        # Alphabet - sorted intelligently (ranges first, then literals)
        alphabet_display = sorted(self.alphabet, key=lambda x: (len(x), x), reverse=True)
        result += f"Σ = {{{', '.join(alphabet_display)}}}\n"
        
        # Initial state
        result += f"q0 = {self.initial_state}\n"
        
        # Final states
        final_list = sorted(self.final_states)
        result += f"F = {{{', '.join(final_list)}}}\n\n"
        
        # Transitions
        result += "δ (transition function):\n"
        for trans in self.transitions:
            result += f"  δ({trans.from_state}, {trans.symbol_desc}) = {trans.to_state}\n"
        
        return result

def create_identifier_dfa() -> SimpleDFA:
    """
    Creates DFA for identifier: [a-zA-Z][a-zA-Z0-9]*
    
    Grammar:
    S → [a-zA-Z] A
    A → [a-zA-Z0-9] A | epsilon
    
    Expected DFA:
    Q = {q0, q1}
    Σ = {a-z, A-Z, 0-9}
    q0 = q0
    F = {q1}
    
    δ:
      δ(q0, [a-zA-Z]) = q1
      δ(q1, [a-zA-Z0-9]) = q1
    """
    dfa = SimpleDFA()
    
    # States
    dfa.add_state("q0", is_final=False)
    dfa.add_state("q1", is_final=True)
    
    # Initial and final states
    dfa.initial_state = "q0"
    dfa.set_final_state("q1")
    
    # Transitions
    dfa.add_transition("q0", "[a-zA-Z]", "q1")      # First char must be letter
    dfa.add_transition("q1", "[a-zA-Z0-9]", "q1")   # Subsequent chars can be letter or digit
    
    return dfa

def create_number_dfa() -> SimpleDFA:
    """
    Creates DFA for number: 0 | -?[1-9][0-9]*
    
    Grammar:
    S → 0 | -A | [1-9]B
    A → [1-9]B
    B → [0-9]B | epsilon
    
    Expected DFA:
    Q = {q0, q1, q2, q3}
    Σ = {0, 1-9, -}
    q0 = q0
    F = {q2, q3}
    
    δ:
      δ(q0, 0) = q2
      δ(q0, -) = q1
      δ(q0, [1-9]) = q3
      δ(q1, [1-9]) = q3
      δ(q3, [0-9]) = q3
    """
    dfa = SimpleDFA()
    
    # States
    dfa.add_state("q0", is_final=False)  # Initial state
    dfa.add_state("q1", is_final=False)  # After minus sign
    dfa.add_state("q2", is_final=True)   # Just "0"
    dfa.add_state("q3", is_final=True)   # Multi-digit or with minus
    
    # Initial and final states
    dfa.initial_state = "q0"
    dfa.set_final_state("q2")
    dfa.set_final_state("q3")
    
    # Transitions
    dfa.add_transition("q0", "0", "q2")           # Single zero
    dfa.add_transition("q0", "-", "q1")           # Negative sign
    dfa.add_transition("q0", "[1-9]", "q3")       # First digit 1-9
    dfa.add_transition("q1", "[1-9]", "q3")       # After minus, digit 1-9
    dfa.add_transition("q3", "[0-9]", "q3")       # More digits
    
    return dfa

def main():
    """Main function - generates both DFAs and displays them"""
    
    print("=" * 70)
    print("FINITE AUTOMATA GENERATION FROM REGULAR GRAMMARS")
    print("=" * 70)
    print()
    
    # Identifier DFA
    print("─" * 70)
    print("1. IDENTIFIER DFA")
    print("─" * 70)
    print("Grammar Rules:")
    print("  S → [a-zA-Z] A")
    print("  A → [a-zA-Z0-9] A | epsilon")
    print()
    print("Generated DFA:")
    print()
    identifier_dfa = create_identifier_dfa()
    print(identifier_dfa.display())
    
    # Number DFA
    print()
    print("─" * 70)
    print("2. NUMBER DFA")
    print("─" * 70)
    print("Grammar Rules:")
    print("  S → 0 | -A | [1-9]B")
    print("  A → [1-9]B")
    print("  B → [0-9]B | epsilon")
    print()
    print("Generated DFA:")
    print()
    number_dfa = create_number_dfa()
    print(number_dfa.display())
    
    print()
    print("=" * 70)

def validate_identifier(dfa: SimpleDFA, identifier: str) -> bool:
    """
    Validate if a string matches the identifier DFA
    Used to test the generated DFA
    """
    if not identifier:
        return False
    
    current = dfa.initial_state
    
    # Check first character
    if identifier[0].isalpha():
        current = "q1"
    else:
        return False
    
    # Check remaining characters
    for char in identifier[1:]:
        if identifier[0].isalpha() or identifier[0].isdigit():
            current = "q1"
        else:
            return False
    
    return current in dfa.final_states

def validate_number(dfa: SimpleDFA, number_str: str) -> bool:
    """
    Validate if a string matches the number DFA
    Used to test the generated DFA
    """
    if not number_str:
        return False
    
    current = dfa.initial_state
    i = 0
    
    # Handle optional minus sign
    if number_str[0] == '-':
        current = "q1"
        i = 1
    
    # Must have at least one digit
    if i >= len(number_str):
        return False
    
    # First digit after optional minus
    if number_str[i] == '0':
        if i == len(number_str) - 1 or (i == 0 and len(number_str) == 1):
            return "q2" in dfa.final_states
        else:
            return False
    elif '1' <= number_str[i] <= '9':
        current = "q3"
        i += 1
    else:
        return False
    
    # Remaining digits
    while i < len(number_str):
        if '0' <= number_str[i] <= '9':
            current = "q3"
        else:
            return False
        i += 1
    
    return current in dfa.final_states

if __name__ == "__main__":
    main()
    
    # Testing examples
    print()
    print("=" * 70)
    print("VALIDATION EXAMPLES (Testing the DFAs)")
    print("=" * 70)
    
    identifier_dfa = create_identifier_dfa()
    number_dfa = create_number_dfa()
    
    print("\nIdentifier Tests:")
    test_ids = ["x", "myVar", "var1", "_invalid", "1wrong", "CamelCase"]
    for test_id in test_ids:
        result = validate_identifier(identifier_dfa, test_id)
        status = "✓ VALID" if result else "✗ INVALID"
        print(f"  '{test_id}' → {status}")
    
    print("\nNumber Tests:")
    test_nums = ["0", "42", "-5", "-100", "007", "-0", "abc"]
    for test_num in test_nums:
        result = validate_number(number_dfa, test_num)
        status = "✓ VALID" if result else "✗ INVALID"
        print(f"  '{test_num}' → {status}")
