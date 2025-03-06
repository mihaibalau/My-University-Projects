package Model.dataStructures.myList;

import java.util.List;
import java.util.ArrayList;

public class MyList<V> implements MyIList<V>{

    List<V> list;

    public MyList(){
        this.list = new ArrayList<V>();
    }

    @Override
    public void add(V value) {
        this.list.add(value);
    }

    @Override
    public List<V> getList() {
        return this.list;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (V item : this.list) {
            sb.append(item).append("\n");
        }
        return sb.toString();
    }
}
