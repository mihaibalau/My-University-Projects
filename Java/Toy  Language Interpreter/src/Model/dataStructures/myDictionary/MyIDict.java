package Model.dataStructures.myDictionary;

import Exceptions.MyException;

import java.util.List;
import java.util.Map;

public interface MyIDict <K, V>{
    V lookup(K key) throws MyException;

    List<K> getKeys();

    public MyIDict<K, V> clone();

    public List<V> getValues();
    String toString();

    Map<K, V> getDict();

    void update(K key, V value);

    boolean isDefined(K key);

    void remove(K key);
}
