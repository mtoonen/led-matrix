package nl.meine.led.backend.resources;

public enum MessageType {

    TEXT ("text"),
    TEXT_SCROLLING ("text_scrolling"),
    SHAPE ("shape"),
    UNDEFINED ("undefined");
    private String type;
    MessageType(String type){
        this.type = type;
    }
}
