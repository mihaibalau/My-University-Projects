package Model.types;

import Model.values.RefValue;
import Model.values.Value;

import java.sql.Ref;

public class RefType implements Type{

    Type inner;

    public RefType(Type _inner){
        this.inner = _inner;
    }

    public Type getInner() {
        return this.inner;
    }


    @Override
    public boolean equals(Object another){
        if (another instanceof  RefType)
            return inner.equals(((RefType) another).getInner());
        else
            return false;
    }

    @Override
    public String toString() { return "Ref(" +inner.toString()+")";}
    @Override
    public Value defaultValue() {
        return new RefValue(0, inner);
    }
}
