package com.sample;

import javax.ws.rs.GET;
import javax.ws.rs.Path;

@Path("")
public class ApiResource {
    @GET
    @Path("/hello")
    public String hello() {
        return "Hello";
    }
}
