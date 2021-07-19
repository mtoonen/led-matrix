package nl.meine.led.backend.resources;

public enum MessageType {

    TEXT ("text");
    private String type;
    MessageType(String type){
        this.type = type;
    }
}
