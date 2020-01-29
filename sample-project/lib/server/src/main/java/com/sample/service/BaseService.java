package com.sample.service;

import com.sample.config.BaseConfig;
import io.dropwizard.setup.Environment;

public abstract class BaseService<T extends BaseConfig> extends AbstractService<T> {

    public BaseService(AbstractServiceBundle bundle) {
        super(bundle);
    }

    public void run(T configuration, Environment environment) throws Exception {
        bundle.run(environment);
//        for (Object managedObject : environment.lifecycle().getManagedObjects()) {
//            if (managedObject instanceof Managed) {
//                ((Managed) managedObject).start();
//            }
//        }
    }
}
