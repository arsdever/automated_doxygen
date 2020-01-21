package com.arsdever;

import com.arsdever.health.TemplateHealthCheck;
import com.arsdever.resources.HelloWorldResource;
import com.google.common.base.Charsets;
import com.google.common.cache.CacheBuilderSpec;
import io.dropwizard.Application;
import io.dropwizard.ConfiguredBundle;
import io.dropwizard.bundles.assets.AssetServlet;
import io.dropwizard.bundles.assets.AssetsBundleConfiguration;
import io.dropwizard.bundles.assets.AssetsConfiguration;
import io.dropwizard.setup.Bootstrap;
import io.dropwizard.setup.Environment;
import io.swagger.config.ScannerFactory;
import io.swagger.jaxrs.config.BeanConfig;
import io.swagger.jaxrs.config.DefaultJaxrsScanner;
import io.swagger.jaxrs.listing.ApiListingResource;
import io.swagger.jaxrs.listing.SwaggerSerializers;

import java.util.Iterator;
import java.util.Map;

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
        ConfiguredBundle bundle = new ConfiguredBundle("/swagger-ui", "/api/", "index.html") {

            public void initialize(Bootstrap<?> bootstrap) {
            }

            public void run(AssetsBundleConfiguration bundleConfig, Environment env) throws Exception {
                AssetsConfiguration config = bundleConfig.getAssetsConfiguration();
                CacheBuilderSpec spec = config.getCacheSpec() != null ? CacheBuilderSpec.parse(config.getCacheSpec()) : this.cacheBuilderSpec;
                Iterable<Map.Entry<String, String>> overrides = config.getOverrides().entrySet();
                Iterable<Map.Entry<String, String>> mimeTypes = config.getMimeTypes().entrySet();
                Object servletResourcePathToUriMappings;
                if (!config.getResourcePathToUriMappings().isEmpty()) {
                    servletResourcePathToUriMappings = config.getResourcePathToUriMappings().entrySet();
                } else {
                    servletResourcePathToUriMappings = this.resourcePathToUriMappings;
                }

                AssetServlet servlet = new AssetServlet((Iterable)servletResourcePathToUriMappings, this.indexFile, Charsets.UTF_8, spec, overrides, mimeTypes);
                Iterator var9 = ((Iterable)servletResourcePathToUriMappings).iterator();

                while(var9.hasNext()) {
                    Map.Entry<String, String> mapping = (Map.Entry)var9.next();
                    String mappingPath = (String)mapping.getValue();
                    if (!mappingPath.endsWith("/")) {
                        mappingPath = mappingPath + '/';
                    }

                    mappingPath = mappingPath + "*";
                    servlet.setCacheControlHeader(config.getCacheControlHeader());
                    LOGGER.info("Registering ConfiguredAssetBundle with name: {} for path {}", this.assetsName, mappingPath);
                    env.servlets().addServlet(this.assetsName, servlet).addMapping(new String[]{mappingPath});
                }

            }
        };
        bootstrap.addBundle();
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
        beanConfig.setDescription("The drpowizard apis");
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