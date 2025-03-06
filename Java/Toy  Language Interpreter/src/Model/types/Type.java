package Model.types;

import Model.values.Value;

public interface Type {
    boolean equals(Object another);
    String toString();
    public Value defaultValue();

}
