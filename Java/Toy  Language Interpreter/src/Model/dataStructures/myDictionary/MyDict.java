package Model.dataStructures.myDictionary;

import Exceptions.MyException;

import java.util.*;

public class MyDict<K, V> implements MyIDict<K,V> {

    Map<K,V> dict;
    public MyDict(){
        dict = new HashMap<K, V>();
    }
    public MyDict(Map <K, V> _dict){
        dict = _dict;
    }

    @Override
    public V lookup(K key) throws MyException {
        if(!dict.containsKey(key))
            throw new MyException("Invalid dictionary key!");
        return this.dict.get(key);
    }

    @Override
    public List<K> getKeys(){
        List<K> returned_list = new ArrayList<>();
        for(K key : this.dict.keySet())
            returned_list.add(key);
        return returned_list;
    }

    @Override
    public MyIDict<K, V> clone() {
        Map<K, V> aux = new HashMap<>(this.dict);
        return new MyDict<K, V>(aux);
    }

    @Override
    public List<V> getValues(){
        return new LinkedList<V>(this.dict.values());
    }

    @Override
    public Map<K, V> getDict(){
        return this.dict;
    }

    @Override
    public void update(K key, V value) {
        this.dict.put(key, value);
    }

    @Override
    public boolean isDefined(K key) {
        return this.dict.containsKey(key);
    }

    @Override
    public void remove(K key) {
        this.dict.remove(key);
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        for (K key : this.dict.keySet())
            s.append(key).append("->").append(this.dict.get(key)).append("\n");
        return s.toString();
    }
}
