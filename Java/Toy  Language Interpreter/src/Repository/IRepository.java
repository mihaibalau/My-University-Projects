package Repository;

import Exceptions.MyException;
import Exceptions.MyIOException;
import Model.prgState.PrgState;
import Model.statements.IStmt;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    void setPrgList(List<PrgState> currentProgram);
    void setPrg(IStmt _currentStmt);
    List<PrgState> getPrgList();
    void logPrgStateExec(PrgState _state) throws MyIOException;

    void printBeforeExec() throws MyIOException;

    void printAfterExec() throws MyIOException ;
}
