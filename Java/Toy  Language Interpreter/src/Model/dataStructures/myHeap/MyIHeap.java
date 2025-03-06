package Model.dataStructures.myHeap;

import Exceptions.MyException;
import Model.values.Value;

import java.util.List;
import java.util.Map;
import java.util.Set;

public interface MyIHeap<A, C> {

    C lookup(A address) throws MyException;

    void update(A address, C content);
    boolean isDefined(A address);
    void remove(A address);
    Integer firstFree();

    void setHeap(Map<A, C> _heap);

    Map<A, C> getHeap();

    Map<Integer, Value> safeCollector(Set<Integer> usedAddresses, Map<Integer, Value> heap);
    public List<C> getValues();
}
