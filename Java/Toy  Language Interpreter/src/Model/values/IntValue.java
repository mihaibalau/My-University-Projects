package Model.values;

import Model.types.IntType;
import Model.types.Type;

public class IntValue implements Value{
    private int value;

    public IntValue(){
        this.value = 0;
    }

    public IntValue(int v){
        this.value = v;
    }
    public int getVal() {
        return this.value;
    }

    @Override
    public String toString(){
        return Integer.toString(this.value);
    }

    @Override
    public boolean equals(Value v){
        if(! v.getType().equals(this.getType()))
            return false;
        return ((IntValue) v).getVal() == this.value;
    }

    @Override
    public Type getType() {
        return new IntType();
    }
}
