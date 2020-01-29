package com.sample.service;

import io.dropwizard.setup.Environment;
import ru.vyarus.dropwizard.guice.GuiceBundle;

public abstract class AbstractServiceBundle extends GuiceBundle {
    public abstract void configureBuilder(GuiceBundle.Builder guiceBuilder);
    public abstract void run(Environment environment);
}
