package com.sample;

import com.google.inject.Inject;

public class SomeClass {
    Boolean bool;

    @Inject
    SomeClass(Boolean bool) {
        this.bool = bool;
    }
}
