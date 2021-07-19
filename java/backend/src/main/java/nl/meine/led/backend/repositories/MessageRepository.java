package nl.meine.led.backend.repositories;

import nl.meine.led.backend.resources.Message;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

public interface MessageRepository extends JpaRepository<Message, Integer> {

    @Query(nativeQuery = true, value ="SELECT * FROM Message m WHERE m.processed = false order by id asc limit 1" )
    Message firstUnprocessed();
}
