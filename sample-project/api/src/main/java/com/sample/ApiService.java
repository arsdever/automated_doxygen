package com.sample;

import com.sample.service.AbstractServiceBundle;
import com.sample.service.AppService;

public class ApiService extends AppService {
    public ApiService(AbstractServiceBundle bundle) {
        super(bundle);
    }

    static public void main(String... args) throws Exception {
        new ApiService(new ApiServiceBundle()).run(args);
    }
}
