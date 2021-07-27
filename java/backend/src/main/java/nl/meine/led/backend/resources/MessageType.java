package nl.meine.led.backend.resources;

public enum MessageType {

    TEXT ("text"),
    SHAPE ("shape"),
    UNDEFINED ("undefined");
    private String type;
    MessageType(String type){
        this.type = type;
    }
}
