import org.antlr.v4.runtime.tree.*;

public class ProductionsVisitor extends MiniDSLBaseVisitor<Void> {
    private final StringBuilder productions = new StringBuilder();

    @Override
    public Void visitProgram(MiniDSLParser.ProgramContext ctx) {
        productions.append("program → statement+ EOF\n");
        visitChildren(ctx);
        return null;
    }

    @Override
    public Void visitStatement(MiniDSLParser.StatementContext ctx) {
        if (ctx.scanStatement() != null) {
            productions.append("statement → scanStatement\n");
        } else if (ctx.monitorStatement() != null) {
            productions.append("statement → monitorStatement\n");
        } else if (ctx.assignment() != null) {
            productions.append("statement → assignment\n");
        } else if (ctx.ifStatement() != null) {
            productions.append("statement → ifStatement\n");
        }
        return visitChildren(ctx);
    }

    @Override
    public Void visitScanStatement(MiniDSLParser.ScanStatementContext ctx) {
        productions.append("scanStatement → SCAN_VEHICLE identifier READ scanTarget\n");
        return super.visitScanStatement(ctx);
    }

    @Override
    public Void visitScanTarget(MiniDSLParser.ScanTargetContext ctx) {
        productions.append("scanTarget → 'error_codes' | 'live_data' | 'freeze_frame' | 'readiness_status'\n");
        return super.visitScanTarget(ctx);
    }

    @Override
    public Void visitMonitorStatement(MiniDSLParser.MonitorStatementContext ctx) {
        productions.append("monitorStatement → MONITOR identifier WARN_IF condition\n");
        return super.visitMonitorStatement(ctx);
    }

    @Override
    public Void visitAssignment(MiniDSLParser.AssignmentContext ctx) {
        productions.append("assignment → identifier ASSIGN expression\n");
        return super.visitAssignment(ctx);
    }

    @Override
    public Void visitIfStatement(MiniDSLParser.IfStatementContext ctx) {
        productions.append("ifStatement → IF condition statement* END\n");
        return super.visitIfStatement(ctx);
    }

    @Override
    public Void visitExpression(MiniDSLParser.ExpressionContext ctx) {
        if (ctx.listExpression() != null) {
            productions.append("expression → listExpression\n");
        } else {
            productions.append("expression → value\n");
        }
        return visitChildren(ctx);
    }

    @Override
    public Void visitListExpression(MiniDSLParser.ListExpressionContext ctx) {
        productions.append("listExpression → LIST ( [ listContent? ] )\n");
        return visitChildren(ctx);
    }

    @Override
    public Void visitListContent(MiniDSLParser.ListContentContext ctx) {
        productions.append("listContent → dictEntry (, dictEntry)*\n");
        return visitChildren(ctx);
    }

    @Override
    public Void visitDictEntry(MiniDSLParser.DictEntryContext ctx) {
        productions.append("dictEntry → { dictPair (, dictPair)* }\n");
        return visitChildren(ctx);
    }

    @Override
    public Void visitDictPair(MiniDSLParser.DictPairContext ctx) {
        productions.append("dictPair → identifier : value\n");
        return visitChildren(ctx);
    }

    @Override
    public Void visitCondition(MiniDSLParser.ConditionContext ctx) {
        if (ctx.simpleCondition() != null) {
            productions.append("condition → simpleCondition\n");
        } else if (ctx.AND() != null) {
            productions.append("condition → condition AND condition\n");
        } else if (ctx.OR() != null) {
            productions.append("condition → condition OR condition\n");
        } else if (ctx.LPAREN() != null) {
            productions.append("condition → ( condition )\n");
        }
        return visitChildren(ctx);
    }

    @Override
    public Void visitSimpleCondition(MiniDSLParser.SimpleConditionContext ctx) {
        productions.append("simpleCondition → comparableValue comparisonOp comparableValue\n");
        return visitChildren(ctx);
    }

    @Override
    public Void visitComparableValue(MiniDSLParser.ComparableValueContext ctx) {
        if (ctx.identifier() != null) {
            productions.append("comparableValue → identifier\n");
        } else {
            productions.append("comparableValue → value\n");
        }
        return visitChildren(ctx);
    }

    @Override
    public Void visitComparisonOp(MiniDSLParser.ComparisonOpContext ctx) {
        String op = ctx.getText();
        productions.append("comparisonOp → ").append(op).append("\n");
        return null;
    }

    @Override
    public Void visitIdentifier(MiniDSLParser.IdentifierContext ctx) {
        productions.append("identifier → IDENTIFIER\n");
        return null;
    }

    @Override
    public Void visitValue(MiniDSLParser.ValueContext ctx) {
        if (ctx.NUMBER() != null) {
            productions.append("value → NUMBER\n");
        } else if (ctx.STRING() != null) {
            productions.append("value → STRING\n");
        } else if (ctx.identifier() != null) {
            productions.append("value → identifier\n");
        }
        return visitChildren(ctx);
    }

    public String getProductions() {
        return productions.toString();
    }
}