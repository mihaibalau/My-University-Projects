package Model.values;

import Model.types.BoolType;
import Model.types.Type;

public class BoolValue implements Value{

    private boolean value;

    public BoolValue(){
        this.value = false;
    }

    public BoolValue(boolean v){
        this.value = v;
    }

    @Override
    public boolean equals(Value v) {
        if(!v.getType().equals(this.getType()))
            return false;
        return ((BoolValue) v).getVal() == this.value;
    }

    @Override
    public Type getType() {
        return new BoolType();
    }

    @Override
    public String toString(){
        if(this.value)
            return "True";
        else
            return "False";
    }

    public boolean getVal() {
        return this.value;
    }
}
