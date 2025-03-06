package Model;

import Model.expressions.*;
import Model.statements.*;
import Model.types.*;
import Model.values.*;
import java.util.ArrayList;
import java.util.List;
public class availablePrograms {

    public static final List<IStmt> availablePrograms = new ArrayList<IStmt>(List.of(

            new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new CompStmt(
                    new AssignStmt("v", new ValueExp(new IntValue(2))),
                    new PrintStmt(new VarExp("v"))
                )
            ),

            new CompStmt(
                new VarDeclStmt("a", new IntType()),
                new CompStmt(
                        new VarDeclStmt("b", new IntType()),
                        new CompStmt(
                                new AssignStmt(
                                        "a",
                                        new ArithExp(
                                                '+',
                                                new ValueExp(new IntValue(2)),
                                                new ArithExp(
                                                        '*',
                                                        new ValueExp(new IntValue(3)),
                                                        new ValueExp(new IntValue(5))
                                                )
                                        )
                                ),
                                new CompStmt(
                                        new AssignStmt(
                                                "b",
                                                new ArithExp(
                                                        '+',
                                                        new VarExp("a"),
                                                        new ValueExp(new IntValue(1))
                                                )
                                        ),
                                        new PrintStmt(new VarExp("b"))
                                )
                        )
                    )
            ),

            new CompStmt(
                new VarDeclStmt("varf", new StringType()),
                new CompStmt(
                        new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                        new CompStmt(
                                new openRFile(new VarExp("varf")),
                                new CompStmt(
                                        new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(
                                                new readFile(new VarExp("varf"), "varc"),
                                                new CompStmt(
                                                        new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(
                                                                new readFile(new VarExp("varf"), "varc"),
                                                                new CompStmt(
                                                                        new PrintStmt(new VarExp("varc")),
                                                                        new closeRFile(new VarExp("varf"))
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
            ),

            new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                    new newStmt("v", new ValueExp(new IntValue(20))),
                    new CompStmt(
                        new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                        new CompStmt(
                            new newStmt("a", new VarExp("v")),
                            new CompStmt(
                                new PrintStmt(new VarExp("v")),
                                new PrintStmt(new VarExp("a"))
                            )
                        )
                    )
                )
            ),


            new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                    new newStmt("v", new ValueExp(new IntValue(20))),
                    new CompStmt(
                            new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                            new CompStmt(
                                    new newStmt("a", new VarExp("v")),
                                    new CompStmt(
                                            new PrintStmt(new readHeapExp(new VarExp("v"))),
                                            new PrintStmt(
                                                    new ArithExp(
                                                            '+',
                                                            new readHeapExp(new readHeapExp(new VarExp("a"))),
                                                            new ValueExp(new IntValue(5))
                                                    )
                                            )
                                    )
                            )
                    )
                )
            ),

            new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                    new newStmt("v", new ValueExp(new IntValue(20))),
                    new CompStmt(
                            new PrintStmt(new readHeapExp(new VarExp("v"))),
                            new CompStmt(
                                    new writeHeapStmt("v", new ValueExp(new IntValue(30))),
                                    new PrintStmt(
                                            new ArithExp(
                                                    '+',
                                                    new readHeapExp(new VarExp("v")),
                                                    new ValueExp(new IntValue(5))
                                            )
                                    )
                            )
                    )
                )
            ),

            new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new CompStmt(
                    new AssignStmt("v", new ValueExp(new IntValue(4))),
                    new CompStmt(
                            new whileStatement(
                                    new RelationalExp(
                                            new VarExp("v"),
                                            new ValueExp(new IntValue(0)),
                                            5
                                    ),
                                    new CompStmt(
                                            new PrintStmt(new VarExp("v")),
                                            new AssignStmt("v",
                                                    new ArithExp(
                                                            '-',
                                                            new VarExp("v"),
                                                            new ValueExp(new IntValue(1))
                                                    )
                                            )
                                    )
                            ),
                            new PrintStmt(new VarExp("v"))
                    )
                )
            ),


            new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                    new newStmt("v", new ValueExp(new IntValue(20))),
                    new CompStmt(
                            new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                            new CompStmt(
                                    new newStmt("a", new VarExp("v")),
                                    new CompStmt(
                                            new newStmt("v", new ValueExp(new IntValue(30))),
                                            new PrintStmt(
                                                    new readHeapExp(
                                                            new readHeapExp(
                                                                    new VarExp("a")
                                                            )
                                                    )
                                            )
                                    )
                            )
                    )
                )
            ),


            new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new CompStmt(
                    new VarDeclStmt("a", new RefType(new IntType())),
                    new CompStmt(
                            new AssignStmt("v", new ValueExp(new IntValue(10))),
                            new CompStmt(
                                    new newStmt("a", new ValueExp(new IntValue(22))),
                                    new CompStmt(
                                            new forkStmt(
                                                    new CompStmt(
                                                            new writeHeapStmt("a", new ValueExp(new IntValue(30))),
                                                            new CompStmt(
                                                                    new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                                    new CompStmt(
                                                                            new PrintStmt(new VarExp("v")),
                                                                            new PrintStmt(new readHeapExp(new VarExp("a")))
                                                                    )
                                                            )
                                                    )
                                            ),
                                            new CompStmt(
                                                    new PrintStmt(new VarExp("v")),
                                                    new PrintStmt(new readHeapExp(new VarExp("a")))
                                            )
                                    )
                            )
                    )
                )
            ),

            new CompStmt(
                    new VarDeclStmt("a", new RefType(new IntType())),
                    new CompStmt(
                            new newStmt("a", new ValueExp(new IntValue(20))),
                            new CompStmt(
                                    new forStmt(
                                            "v",
                                            new ValueExp(new IntValue(0)),
                                            new ValueExp(new IntValue(3)),
                                            new ArithExp(
                                                    '+',
                                                    new VarExp("v"),
                                                    new ValueExp(new IntValue(1))
                                            ),
                                            new forkStmt(
                                                    new CompStmt(
                                                            new PrintStmt(new VarExp("v")),
                                                            new AssignStmt(
                                                                    "v",
                                                                    new ArithExp(
                                                                            '*',
                                                                            new VarExp("v"),
                                                                            new readHeapExp(new VarExp("a"))
                                                                    )
                                                            )
                                                    )
                                            )
                                    ),
                                    new PrintStmt(new readHeapExp(new VarExp("a")))
                            )
                    )
            )
        )
    );
}
