package Model.prgState;

import Exceptions.MyException;
import Exceptions.MyIOException;
import Model.dataStructures.myDictionary.MyDict;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myList.MyIList;
import Model.dataStructures.myList.MyList;
import Model.dataStructures.myHeap.MyHeap;
import Model.dataStructures.myHeap.MyIHeap;
import Model.dataStructures.myStack.MyIStack;
import Model.dataStructures.myStack.MyStack;
import Model.statements.CompStmt;
import Model.statements.IStmt;
import Model.values.RefValue;
import Model.values.StringValue;
import Model.values.Value;

import java.io.BufferedReader;
import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

public class PrgState {

    MyIStack<IStmt> exeStack;
    MyIDict<String, Value> symTable;
    MyIList<Value> out;
    MyIDict<StringValue, BufferedReader> fileTable;
    MyIHeap<Integer, Value> heap;
    IStmt originalProgram;
    private final int id;
    private static final AtomicInteger idInc = new AtomicInteger(0);

    public PrgState(MyIStack<IStmt> stk, MyIDict<String, Value> symtbl, MyIList<Value> ot, MyIDict<StringValue, BufferedReader> _fileTable, MyIHeap<Integer, Value> _heap, IStmt prg){
        this.exeStack = stk;
        this.symTable = symtbl;
        this.out = ot;
        this.originalProgram = deepCopy(prg);
        this.exeStack.push(prg);
        this.fileTable = _fileTable;
        this.heap = _heap;
        id = idInc.getAndIncrement();
    }

    public PrgState(){
        this.exeStack = new MyStack<>();
        this.symTable = new MyDict<>();
        this.out = new MyList<>();
        this.fileTable = new MyDict<>();
        this.heap = new MyHeap<>();
        id = idInc.getAndIncrement();
    }

    public PrgState(IStmt prg){
        this.exeStack = new MyStack<>();
        this.symTable = new MyDict<>();
        this.out = new MyList<>();
        this.fileTable = new MyDict<>();
        this.heap = new MyHeap<>();
        this.exeStack.push(prg);
        id = idInc.getAndIncrement();
    }


    public MyIStack<IStmt> getExeStack(){
        return this.exeStack;
    }

    public MyIDict<String, Value> getSymTable(){
        return this.symTable;
    }

    public MyIList<Value> getOut(){
        return this.out;
    }

    public MyIDict<StringValue, BufferedReader> getFileTable(){
        return this.fileTable;
    }

    public MyIHeap<Integer, Value> getHeap(){
        return this.heap;
    }

    public void setExeStack(MyIStack<IStmt> stk){
        this.exeStack = stk;
    }

    public void setSymTable(MyIDict<String, Value> symtbl){
        this.symTable = symtbl;
    }

    public void setOut(MyIList<Value> ot){
        this.out = ot;
    }

    public void setFileTable(MyIDict<StringValue, BufferedReader> _fileTable){
        this.fileTable = _fileTable;
    }

//    public Set<Integer> getUsedAddresses(){
//        Set<Integer> usedAddresses = new HashSet<>();
//        for(Value val : this.symTable.getValues()){
//            if(val instanceof RefValue refValue){
//                usedAddresses.add(refValue.getAddr());
//            }
//        }
//        return usedAddresses;
//    }

    public Boolean isNotCompleted(){
        return !this.exeStack.isEmpty();
    }

    public PrgState oneStep() throws MyException, MyIOException {
        if(exeStack.isEmpty())
            throw  new MyException("Program Stack is empty when you try to use on PrgState class");
        IStmt crtStmt = this.exeStack.pop();
        return crtStmt.execute(this);
    }

    @Override
    public String toString(){

        StringBuilder str =  new StringBuilder();
        str.append(" ~ Program State | ID: ").append(id).append(" ~ \n");
        str.append("I) Exe Stack:\n");

        if (!this.exeStack.isEmpty()) {
            IStmt stmt = exeStack.peek();

            while (stmt instanceof CompStmt) {
                CompStmt comp = (CompStmt) stmt;
                str.append(" ").append(comp.getFirst().toString()).append("\n");
                stmt = comp.getSecond();
            }
            str.append(" ").append(stmt.toString()).append("\n");
        }
        str.append("II) Sym Table: \n");
        str.append(this.symTable.toString());
        str.append("III) Out:\n");
        str.append(this.out.toString());
        str.append("IV) FileTable:\n");
        str.append(this.fileTable.toString());
        str.append("\n");
        str.append("V) Heap:\n");
        str.append(this.heap.toString());
        str.append("\n");

        return str.toString();
    }

    IStmt deepCopy(IStmt state){
        return state;
    }
}
