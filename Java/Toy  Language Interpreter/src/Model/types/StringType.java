package Model.types;

import Model.values.StringValue;
import Model.values.Value;

public class StringType implements Type{

    @Override
    public boolean equals(Object another){
        return another instanceof StringType;
    }

    @Override
    public String toString(){
        return "string";
    }

    @Override
    public Value defaultValue() {
        return new StringValue(" ");
    }
}
