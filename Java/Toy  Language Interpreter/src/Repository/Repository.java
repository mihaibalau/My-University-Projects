package Repository;

import Exceptions.MyException;
import Exceptions.MyIOException;
import Model.dataStructures.myDictionary.MyDict;
import Model.prgState.PrgState;
import Model.statements.IStmt;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{

    private List<PrgState> prgState = new ArrayList<>();
    private String logFilePath;

    public Repository(PrgState _prgState){
        this.prgState.add(_prgState);
    }

    public Repository(String _logFilePath) {
        this.logFilePath = _logFilePath;
    }

    public Repository(PrgState _prgState, String _logFilePath){
        this.prgState.add(_prgState);
        this.logFilePath = _logFilePath;
    }

    public void printBeforeExec() throws MyIOException {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
            logFile.print("\n****** Before code execution ****** \n");
            logFile.close();
        } catch (IOException e){
            throw new MyIOException(e.toString());
        }
    }

    public void printAfterExec() throws MyIOException {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
            logFile.print("\n##### After the execution ###### \n");
            logFile.close();
        } catch (IOException e){
            throw new MyIOException(e.toString());
        }
    }

    @Override
    public void setPrgList(List<PrgState> currentProgram) {
        this.prgState = currentProgram;
    }

    @Override
    public void setPrg(IStmt _currentStmt){
        this.prgState = new ArrayList<>();
        this.prgState.add(new PrgState(_currentStmt));
    }

    @Override
    public List<PrgState> getPrgList() {
        return this.prgState;
    }

    @Override
    public void logPrgStateExec(PrgState _state) throws MyIOException {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
            logFile.println("\n----[ NEW LOG STARTING ]----\n");
            logFile.print(_state.toString());
            logFile.print("\n------[ LOG ENDED ]------\n");
            logFile.close();
        } catch (IOException e) {
            throw new MyIOException(e.toString());
        }
    }
}
