package Model.values;

import Model.types.Type;

public interface Value {
    boolean equals(Value v);

    Type getType();

}
