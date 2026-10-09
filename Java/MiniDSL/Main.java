import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;

import java.util.*;
import java.util.regex.Pattern;

private enum TokenType{
    // Keywords
    SCAN_VEHICLE, MONITOR, WARN_IF, ERROR_IF,
    READ, LIST, IF, ELSE, FOR, IN, PRINT, END,

    // Identifiers and Constants
    IDENTIFIER, NUMBER, STRING,

    // Operators and Delimiters
    ASSIGN,
    PLUS, MINUS,
    SELECT, // ->
    FILTER, // ?
    COLON,
    COMMA,
    SEMICOLON,
    DOT,

    // Comparison Operators
    EQ, NEQ,
    LT, GT, LTE, GTE,
    AND, OR,

    // Delimiters
    LPAREN, RPAREN,
    LBRACE, RBRACE,
    LBRACKET, RBRACKET,

    // SPECIAL
    EOF, UNKNOWN

}

private static class Token {
    public TokenType type;
    public String lexeme;
    public Object literal;
    public int line;
    public int column;

    public Token(TokenType type, String lexeme, Object literal, int line, int column) {
        this.type = type;
        this.lexeme = lexeme;
        this.literal = literal;
        this.line = line;
        this.column = column;
    }

    @Override
    public String toString() {
        return type + ": " + lexeme + " (" + line + ", " + column + ")";
    }
}

private class Scanner {
    private String source;
    private List<Token> tokens;
    private int start = 0;
    private int current = 0;
    private int line = 1;
    private int column = 1;

    private static final Map<String, TokenType> KEYWORDS = new HashMap<>();
    static {
        KEYWORDS.put("SCAN_VEHICLE", TokenType.SCAN_VEHICLE);
        KEYWORDS.put("MONITOR", TokenType.MONITOR);
        KEYWORDS.put("WARN_IF", TokenType.WARN_IF);
        KEYWORDS.put("ERROR_IF", TokenType.ERROR_IF);
        KEYWORDS.put("READ", TokenType.READ);
        KEYWORDS.put("LIST", TokenType.LIST);
        KEYWORDS.put("IF", TokenType.IF);
        KEYWORDS.put("ELSE", TokenType.ELSE);
        KEYWORDS.put("FOR", TokenType.FOR);
        KEYWORDS.put("IN", TokenType.IN);
        KEYWORDS.put("PRINT", TokenType.PRINT);
        KEYWORDS.put("END", TokenType.END);
        KEYWORDS.put("AND", TokenType.AND);
        KEYWORDS.put("OR", TokenType.OR);

    }

    private static final Pattern IDENTIFIER_PATTERN = Pattern.compile("^[a-zA-Z_][a-zA-Z0-9_]*$");

    private boolean isValidIdentifier(String text) {
        return IDENTIFIER_PATTERN.matcher(text).matches();
    }

    private static final Pattern NUMBER_PATTERN = Pattern.compile("^(0|-?[1-9]\\d*)$");

    private boolean isValidNumber(String text) {
        return NUMBER_PATTERN.matcher(text).matches();
    }

    private static final Pattern STRING_PATTERN = Pattern.compile("^\"[a-zA-Z0-9]*\"$");

    private boolean isValidString(String text) {
        return STRING_PATTERN.matcher(text).matches();
    }

    public List<Token> scanTokens(String source) {
        this.source = source;
        this.tokens = new ArrayList<>();

        while(!isAtEnd()) {
            skipWhitespaceAndComments();
            start = current;

            if(!isAtEnd()) {
                scanToken();
            }
        }

        tokens.add(new Token(TokenType.EOF, "", null, line, column));
        return tokens;
    }

    private void scanToken() {
        char c = advance();

        switch (c) {
            case '(': addToken(TokenType.LPAREN); break;
            case ')': addToken(TokenType.RPAREN); break;
            case '{': addToken(TokenType.LBRACE); break;
            case '}': addToken(TokenType.RBRACE); break;
            case '[': addToken(TokenType.LBRACKET); break;
            case ']': addToken(TokenType.RBRACKET); break;
            case ',': addToken(TokenType.COMMA); break;
            case ':': addToken(TokenType.COLON); break;
            case ';': addToken(TokenType.SEMICOLON); break;
            case '.': addToken(TokenType.DOT); break;
            case '?': addToken(TokenType.SELECT); break;

            case '+':
                addToken(TokenType.PLUS);
                break;

            case '-':
                if(isDigit(peek()))
                    scanNumber();
                else if(match('>'))
                    addToken(TokenType.SELECT);
                else
                    addToken(TokenType.MINUS);
                break;

            case '=':
                if (match('='))
                    addToken(TokenType.EQ);
                else
                    addToken(TokenType.ASSIGN);
                break;

            case '!':
                if (match('=')) {
                    addToken(TokenType.NEQ);
                } else {
                    addToken(TokenType.UNKNOWN);
                }
                break;

            case '<':
                if (match('='))
                    addToken(TokenType.LTE);
                else
                    addToken(TokenType.LT);
                break;

            case '>':
                if (match('='))
                    addToken(TokenType.GTE);
                else
                    addToken(TokenType.GT);
                break;

            case '"':
                scanString();
                break;

            default:
                if (isDigit(c)) {
                    current--;
                    scanNumber();
                } else if (isAlpha(c)) {
                    current--;
                    scanIdentifier();
                } else
                    addToken(TokenType.UNKNOWN);
                break;
        }
    }

    // δ(q0, [a-zA-Z]) = q1
    // δ(q1, [a-zA-Z0-9]) = q1
    private void scanIdentifier() {
        int startPos = current;

        if(!isAlpha(peek())) {
            addToken(TokenType.UNKNOWN);
            return;
        }

        advance();
        while(!isAtEnd() && isAlphaNumeric(peek())) {
            advance();
        }

        String text = source.substring(startPos, current);

        if(!isValidIdentifier(text)) {
            addToken(TokenType.UNKNOWN, text);
            return;
        }

        TokenType type = KEYWORDS.getOrDefault(text, TokenType.IDENTIFIER);
        addToken(type, text);

    }

    // δ(q0, 0) = q2 (final)
    // δ(q0, -) = q1
    // δ(q0, [1-9]) = q3 (final)
    // δ(q1, [1-9]) = q3 (final)
    // δ(q3, [0-9]) = q3 (final)
    private void scanNumber() {
        int startPos = current;

        if (peek() == '-') {
            advance();
        }

        if (isAtEnd() || !isDigit(peek())) {
            addToken(TokenType.UNKNOWN);
            return;
        }

        if (peek() == '0') {
            advance();
            if (!isAtEnd() && isDigit(peek())) {
                addToken(TokenType.UNKNOWN);
                return;
            }
        } else if (isDigit(peek())) {
            advance();
            while (!isAtEnd() && isDigit(peek())) {
                advance();
            }
        }

        String text = source.substring(startPos, current);

        if (!isValidNumber(text)) {
            addToken(TokenType.UNKNOWN, text);
            return;
        }

        int value = Integer.parseInt(text);
        addToken(TokenType.NUMBER, text, value);
    }

    private void scanString() {
        int startPos = current - 1;

        while (!isAtEnd() && peek() != '"') {
            if (peek() == '\n')
                line++;
            advance();
        }

        if (isAtEnd()) {
            addToken(TokenType.UNKNOWN);
            return;
        }

        advance();
        String text = source.substring(startPos, current);

        if (!isValidString(text)) {
            addToken(TokenType.UNKNOWN, text);
            return;
        }

        String value = text.substring(1, text.length() - 1);
        addToken(TokenType.STRING, text, value);
    }

    private void addToken(TokenType type) {
        addToken(type, source.substring(start, current), null);
    }

    private void addToken(TokenType type, String lexeme) {
        addToken(type, lexeme, null);
    }

    private void addToken(TokenType type, String lexeme, Object literal) {
        tokens.add(new Token(type, lexeme, literal, line, column - lexeme.length()));
    }

    private void skipWhitespaceAndComments() {
        while (!isAtEnd()) {
            char c = peek();

            if (c == ' ' || c == '\r' || c == '\t') {
                advance();
            } else if (c == '\n') {
                line++;
                column = 0;
                advance();
            } else if (c == '/' && peekNext() == '/') {
                while (!isAtEnd() && peek() != '\n')
                    advance();
            } else {
                break;
            }
        }
    }

    private char peek() {
        if(isAtEnd())
            return '\0';
        return source.charAt(current);
    }

    private char advance() {
        column++;
        return source.charAt(current++);
    }

    private char peekNext() {
        if(current + 1 >= source.length())
            return '\0';
        return source.charAt(current + 1);
    }

    private boolean match(char expected) {
        if (isAtEnd())
            return false;
        if (source.charAt(current) != expected)
            return false;
        current++;
        column++;
        return true;
    }

    private boolean isAtEnd() {
        return current >= source.length();
    }

    private boolean isAlpha(char c) {
        return (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                c == '_';
    }

    private boolean isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    private boolean isAlphaNumeric(char c) {
        return isAlpha(c) || isDigit(c);
    }
}


void main() {
    // Test source code
    String dslCode = """
        SCAN_VEHICLE diagnostic_tool READ error_codes
        results = List([{code: "P0101"}])
        MONITOR engineTemp WARN_IF engineTemp > 95
        if engineTemp >= 100
            print results
        end
        """;

    // ====== PHASE 1: SCANNING ======
    Scanner scanner = new Scanner();
    List<Token> tokens = scanner.scanTokens(dslCode);

    System.out.println("=== PHASE 1: LEXICAL ANALYSIS (SCANNING) ===\n");
    System.out.println("Tokens generated:");

    for (Token token : tokens) {
        if (token.type == TokenType.EOF) continue;
        if (token.literal != null) {
            System.out.printf("[%-15s] lexeme='%-20s' literal=%s at (%d, %d)%n",
                    token.type, token.lexeme, token.literal, token.line, token.column);
        } else {
            System.out.printf("[%-15s] lexeme='%-20s' at (%d, %d)%n",
                    token.type, token.lexeme, token.line, token.column);
        }
    }

    long totalTokens = tokens.stream().filter(t -> t.type != TokenType.EOF).count();
    long identifiers = tokens.stream().filter(t -> t.type == TokenType.IDENTIFIER).count();
    long numbers = tokens.stream().filter(t -> t.type == TokenType.NUMBER).count();
    long strings = tokens.stream().filter(t -> t.type == TokenType.STRING).count();
    long keywords = tokens.stream().filter(t -> isKeyword(t.type)).count();
    long operators = tokens.stream().filter(t -> isOperator(t.type)).count();
    long unknown = tokens.stream().filter(t -> t.type == TokenType.UNKNOWN).count();

    System.out.println("\n   Total Tokens: " + totalTokens);
    System.out.println("   Keywords: " + keywords);
    System.out.println("   Identifiers: " + identifiers);
    System.out.println("   Numbers: " + numbers);
    System.out.println("   Strings: " + strings);
    System.out.println("   Operators: " + operators);
    System.out.println("   Unknown/Errors: " + unknown);

    // ====== PHASE 2: SYNTACTIC ANALYSIS (PARSING) ======
    System.out.println("\n=== PHASE 2: SYNTACTIC ANALYSIS (PARSING) ===\n");

    try {
        // Create ANTLR input stream from DSL code
        CharStream input = CharStreams.fromString(dslCode);

        // Create lexer
        MiniDSLLexer lexer = new MiniDSLLexer(input);
        CommonTokenStream tokenStream = new CommonTokenStream(lexer);

        // Create parser
        MiniDSLParser parser = new MiniDSLParser(tokenStream);

        // Parse - generate parse tree
        MiniDSLParser.ProgramContext tree = parser.program();

        // ====== PHASE 3: GENERATE PRODUCTIONS ======
        System.out.println("\n=== PHASE 3: GENERATE PRODUCTIONS ===\n");

        ProductionsVisitor visitor = new ProductionsVisitor();
        visitor.visit(tree);

        String productions = visitor.getProductions();

        System.out.println("Productions used during parsing:");
        System.out.println(productions);

        // ====== PARSE TREE VISUALIZATION ======
        System.out.println("\n=== PARSE TREE (Visual Representation) ===\n");
        System.out.println(tree.toStringTree(parser));

    } catch (Exception e) {
        System.err.println("ERROR during parsing: " + e.getMessage());
        e.printStackTrace();
    }
}


private static boolean isKeyword(TokenType type) {
    return type == TokenType.SCAN_VEHICLE ||
            type == TokenType.MONITOR ||
            type == TokenType.WARN_IF ||
            type == TokenType.ERROR_IF ||
            type == TokenType.READ ||
            type == TokenType.LIST ||
            type == TokenType.IF ||
            type == TokenType.ELSE ||
            type == TokenType.FOR ||
            type == TokenType.IN ||
            type == TokenType.PRINT ||
            type == TokenType.END ||
            type == TokenType.AND ||
            type == TokenType.OR;
}

private static boolean isOperator(TokenType type) {
    return type == TokenType.ASSIGN ||
            type == TokenType.PLUS ||
            type == TokenType.MINUS ||
            type == TokenType.SELECT ||
            type == TokenType.FILTER ||
            type == TokenType.EQ ||
            type == TokenType.NEQ ||
            type == TokenType.LT ||
            type == TokenType.GT ||
            type == TokenType.LTE ||
            type == TokenType.GTE;
}
