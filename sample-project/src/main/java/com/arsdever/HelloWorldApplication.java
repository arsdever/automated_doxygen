package com.arsdever;

import com.arsdever.health.TemplateHealthCheck;
import com.arsdever.resources.HelloWorldResource;
import io.dropwizard.Application;
import io.dropwizard.setup.Bootstrap;
import io.dropwizard.setup.Environment;
import io.swagger.config.ScannerFactory;
import io.swagger.jaxrs.config.BeanConfig;
import io.swagger.jaxrs.config.DefaultJaxrsScanner;
import io.swagger.jaxrs.listing.ApiListingResource;
import io.swagger.jaxrs.listing.SwaggerSerializers;

public class HelloWorldApplication extends Application<HelloWorldConfiguration> {
    public static void main(String[] args) throws Exception {
        new HelloWorldApplication().run(args);
    }

    @Override
    public String getName() {
        return "hello-world";
    }

    @Override
    public void initialize(Bootstrap<HelloWorldConfiguration> bootstrap) {
    }

    private void initSwagger(HelloWorldConfiguration configuration, Environment environment) {
        // Swagger Resource
        // The ApiListingResource creates the swagger.json file at localhost:8080/swagger.json
        environment.jersey().register(new ApiListingResource());
        environment.jersey().register(SwaggerSerializers.class);

        Package objPackage = this.getClass().getPackage();
        String version = objPackage.getImplementationVersion();

        // Swagger Scanner, which finds all the resources for @Api Annotations
        ScannerFactory.setScanner(new DefaultJaxrsScanner());

        //This is what is shown when you do "http://localhost:8080/swagger-ui/"
        BeanConfig beanConfig = new BeanConfig();
        beanConfig.setVersion(version);
        beanConfig.setDescription("The dropwizard apis");
        beanConfig.setResourcePackage("ca.gaudreault.mydropwizardapp");
        beanConfig.setScan(true);
    }

    @Override
    public void run(HelloWorldConfiguration configuration,
                    Environment environment) {
        HelloWorldResource resource = new HelloWorldResource(
                configuration.getTemplate(),
                configuration.getDefaultName()
        );
        final TemplateHealthCheck healthCheck =
                new TemplateHealthCheck(configuration.getTemplate());

        initSwagger(configuration, environment);

        environment.healthChecks().register("template", healthCheck);
        environment.jersey().register(resource);
    }
}