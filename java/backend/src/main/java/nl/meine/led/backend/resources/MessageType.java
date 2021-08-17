package nl.meine.led.backend.resources;

import com.fasterxml.jackson.annotation.JsonValue;

public enum MessageType {

    TEXT ("text"),
    TEXT_SCROLLING ("text_scrolling"),
    SHAPE ("shape"),
    UNDEFINED ("undefined");
    @JsonValue
    private String type;
    MessageType(String type){
        this.type = type;
    }
}
