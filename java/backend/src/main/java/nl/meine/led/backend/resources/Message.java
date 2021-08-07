package nl.meine.led.backend.resources;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.awt.*;

@Entity
@Data
public class Message {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;
    private String payload;
    private MessageType type;
    private Integer r;
    private Integer g;
    private Integer b;


    private Boolean processed = false;


}
