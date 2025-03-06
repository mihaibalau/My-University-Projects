package Model.values;

import Model.types.RefType;
import Model.types.Type;

public class RefValue implements Value{

    int address;
    Type locationType;

    public RefValue(Integer nextFreeAddress, Type type) {
        this.address = nextFreeAddress;
        this.locationType = type;
    }

    public Type getLocationType(){
        return locationType;
    }

    public int getAddr(){
        return address;
    }

    @Override
    public boolean equals(Value v) {
        return false;
    }

    @Override
    public Type getType() {
        return new RefType(locationType);
    }

    @Override
    public String toString(){
        return "Ref(" + this.address + ", " + this.locationType + ")";
    }
}
