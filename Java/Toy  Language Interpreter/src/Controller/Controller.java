package Controller;

import Exceptions.MyException;
import Exceptions.MyIOException;
import Model.dataStructures.myDictionary.MyDict;
import Model.dataStructures.myHeap.MyIHeap;
import Model.prgState.PrgState;
import Model.statements.IStmt;
import Model.values.RefValue;
import Model.values.Value;
import Repository.IRepository;

import java.io.IOException;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {

    IRepository repo;
    boolean print_mode;
    ExecutorService executor;

    public Controller(IRepository _repo) {
        this.repo = _repo;
        this.print_mode = false;
    }

    public Controller(IRepository _repo, boolean _print_mode) {
        this.repo = _repo;
        this.print_mode = _print_mode;
    }

    public void setProgram(IStmt _prgState) throws MyException{
        _prgState.typeCheck(new MyDict<>());
        repo.setPrg(_prgState);
    }

    public List<PrgState> getPrgStates(){
        return this.repo.getPrgList();
    }

    public void oneStep() throws MyException, InterruptedException, MyIOException {
        executor = Executors.newFixedThreadPool(2);
        List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());

        if(prgList.isEmpty())
            throw  new MyException("No more program states to be executed!");

        PrgState prg = prgList.get(0);
        MyIHeap<Integer, Value> heap = prg.getHeap();
        heap.setHeap(heap.safeCollector(this.getUsedAddresses(), heap.getHeap()));

        this.oneStepForAllPrg(prgList);
        executor.shutdownNow();
        repo.setPrgList(prgList);

    }

    public void oneStepForAllPrg(List <PrgState> prgList) throws InterruptedException, MyIOException {
        this.repo.printBeforeExec();
        prgList.forEach(prg-> {
            try {
                repo.logPrgStateExec(prg);
            } catch (MyIOException e) {
                throw new RuntimeException(e);
            }
        });

        List<Callable<PrgState>> callList =
                prgList.stream().map((PrgState p) -> (Callable<PrgState>) (() -> { return p.oneStep();})) .collect(Collectors.toList());
        List<PrgState> newPrgList = executor.invokeAll(callList).stream().map(future ->
        {
            try {
                return future.get();
            } catch (InterruptedException | ExecutionException e) {
                throw new RuntimeException(e.toString());
            }
        }).filter(p -> p!=null).collect(Collectors.toList());

        prgList.addAll(newPrgList);
        prgList.forEach(prg -> {
            try {
                repo.logPrgStateExec(prg);
            } catch (MyIOException e) {
                throw new RuntimeException(e);
            }
        });
        this.repo.printAfterExec();
        repo.setPrgList(prgList);
    }


    public void fullExecution() throws MyException, InterruptedException, MyIOException {
        this.executor = Executors.newFixedThreadPool(2);
        List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());

        while(!prgList.isEmpty()) {

            PrgState prg = prgList.get(0);
            MyIHeap<Integer, Value> heap = prg.getHeap();
            heap.setHeap(heap.safeCollector(this.getUsedAddresses(), heap.getHeap()));

            oneStepForAllPrg(prgList);
            prgList = removeCompletedPrg(repo.getPrgList());
        }

        this.executor.shutdownNow();
        this.repo.setPrgList(prgList);
    }

    List<PrgState> removeCompletedPrg(List<PrgState> inPrgList){
        return inPrgList.stream().filter(p -> p.isNotCompleted()).collect(Collectors.toList());
    }

    public Set<Integer> getUsedAddresses() {
        List<PrgState> prgList = this.repo.getPrgList();
        Set<Integer> usedAddresses = new HashSet<>();
        for(PrgState prg : prgList){
            for(Value val : prg.getSymTable().getValues()) {
                if (val instanceof RefValue refVal)
                    usedAddresses.add(refVal.getAddr());
            }
        }
        for(Value val : prgList.get(0).getHeap().getValues()){
            if(val instanceof  RefValue refVal)
                usedAddresses.add(refVal.getAddr());
        }
        return usedAddresses;

    }

}
