package Model.dataStructures.myHeap;

import Exceptions.MyException;
import Model.values.Value;

import java.util.*;
import java.util.stream.Collectors;

public class MyHeap<A, C> implements MyIHeap<A, C>{

    Map<A, C> heap;
    Integer firstFreePos;

    public MyHeap(){
        this.heap = new HashMap<A, C>();
        this.firstFreePos = 1;
    }

    public Map<Integer, Value> safeCollector(Set<Integer> usedAddresses, Map<Integer, Value> heap){
        return heap.entrySet().stream().
                filter(entry -> usedAddresses.contains(entry.getKey())).
                collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    @Override
    public Map<A, C> getHeap(){
        return this.heap;
    }

    @Override
    public void setHeap(Map<A, C> _heap){
        this.heap = _heap;
    }


    @Override
    public C lookup(A address) throws MyException {
        if(!heap.containsKey(address))
            throw new MyException("Invalid heap address!");
        return this.heap.get(address);
    }

    @Override
    public void update(A address, C content) {
        this.heap.put(address, content);
    }

    @Override
    public boolean isDefined(A address) {
        return this.heap.containsKey(address);
    }

    @Override
    public void remove(A address) {
        this.heap.remove(address);
    }

    @Override
    public Integer firstFree() {
        return this.firstFreePos++;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        for (A address : this.heap.keySet())
            s.append(address).append("->").append(this.heap.get(address)).append("\n");
        return s.toString();
    }

    @Override
    public List<C> getValues() {
        return new LinkedList<>(this.heap.values());
    }
}
