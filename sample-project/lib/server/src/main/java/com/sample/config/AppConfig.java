package com.sample.config;

import com.fasterxml.jackson.annotation.JsonProperty;

public class AppConfig extends BaseConfig {
    @JsonProperty
    public AppConfig something;
}
