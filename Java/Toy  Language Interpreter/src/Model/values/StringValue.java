package Model.values;

import Model.types.StringType;
import Model.types.Type;

public class StringValue implements Value{

    private String value;

    public StringValue(){
        this.value = " ";
    }

    public StringValue(String _val){
        this.value = _val;
    }

    public String getValue(){
        return this.value;
    }

    @Override
    public boolean equals(Value v) {
        if(!v.getType().equals(this.getType()))
            return false;
        return ((StringValue) v).getValue().equals(this.value);
    }

    @Override
    public Type getType() {
        return new StringType();
    }

    @Override
    public String toString(){
        return this.value;
    }
}
