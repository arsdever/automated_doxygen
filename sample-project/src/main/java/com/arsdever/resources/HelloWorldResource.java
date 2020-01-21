package com.arsdever.resources;

import com.arsdever.api.Saying;
import com.codahale.metrics.annotation.Timed;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiResponse;
import io.swagger.annotations.ApiResponses;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import java.util.Optional;
import java.util.concurrent.atomic.AtomicLong;

@Path("/hello-world")
@Api(value = "/hello-world", description = "Give a greeting")
@Produces(MediaType.APPLICATION_JSON)
public class HelloWorldResource {
    private final String template;
    private final String defaultName;
    private final AtomicLong counter;
    private final Logger logger = LoggerFactory.getLogger(HelloWorldResource.class);

    public HelloWorldResource(String template, String defaultName) {
        this.template = template;
        this.defaultName = defaultName;
        this.counter = new AtomicLong();
    }

    @GET
    @Timed
    @ApiOperation(value="Return a simple greeting", notes="some day this will do more, it believes in a growth mentality.")
    @ApiResponses(value={
            @ApiResponse(code=200, message="Hello, {name}!"),
            @ApiResponse(code=400, message="Invalid ID")
    })
    public Saying sayHello(@QueryParam("name") Optional<String> name) {
        final String value = String.format(template, name.orElse(defaultName));
        logger.error("Error string");
        return new Saying(counter.incrementAndGet(), value);
    }
}