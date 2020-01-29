package com.sample;

import com.sample.service.AbstractServiceBundle;
import io.dropwizard.setup.Environment;
import ru.vyarus.dropwizard.guice.GuiceBundle;

public class ApiServiceBundle extends AbstractServiceBundle {
    @Override
    public void configureBuilder(GuiceBundle.Builder guiceBuilder) {
        guiceBuilder.modules(new ApiModule());
    }

    @Override
    public void run(Environment environment) {
        environment.jersey().register(ApiResource.class);
    }
}
