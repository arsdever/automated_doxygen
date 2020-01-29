package com.sample.service;

import com.google.inject.Stage;
import io.dropwizard.Application;
import io.dropwizard.Configuration;
import io.dropwizard.setup.Bootstrap;
import ru.vyarus.dropwizard.guice.GuiceBundle;

public abstract class AbstractService<T extends Configuration> extends Application<T> {
    AbstractServiceBundle bundle;

    AbstractService(AbstractServiceBundle bundle) {
        this.bundle = bundle;
    }

    @Override
    public void initialize(Bootstrap<T> bootstrap) {
        GuiceBundle.Builder guiceBuilder = GuiceBundle.builder();

        configureGuiceBuilder(guiceBuilder);

        GuiceBundle guiceBundle = guiceBuilder.build(Stage.DEVELOPMENT);
        bootstrap.addBundle(guiceBundle);
    }

    public void configureGuiceBuilder(GuiceBundle.Builder guiceBuilder) {
        bundle.configureBuilder(guiceBuilder);
    }
}
