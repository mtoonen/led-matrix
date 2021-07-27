package nl.meine.led.backend.controllers;

import javassist.NotFoundException;
import nl.meine.led.backend.repositories.MessageRepository;
import nl.meine.led.backend.resources.Message;
import nl.meine.led.backend.resources.MessageType;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@RequestMapping("messages")
@RestController
public class MessageController {

    @Autowired
    private MessageRepository repo;

    @GetMapping("/all")
    public List<Message> getAll(){
        return repo.findAll();
    }

    @GetMapping("/unprocessed")
    public Message getFirstUnprocessed(){
        return repo.firstUnprocessed();
    }

    @PostMapping("/save")
    public Message save(@RequestBody Message msg){
        msg = repo.save(msg);
        return msg;
    }

    @GetMapping("/processed/{id}")
    public void setProcessed(@PathVariable int id){
        Message msg = repo.findById(id).orElseThrow();
        msg.setProcessed(true);
        repo.save(msg);
    }
}
