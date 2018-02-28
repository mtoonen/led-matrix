/*
 * The MIT License
 *
 * Copyright 2018 Meine Toonen.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
package nl.meine.led.server.hibernate;

import java.io.Serializable;
import java.util.Date;
import javax.persistence.Entity;
import javax.persistence.EnumType;
import javax.persistence.Enumerated;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

/**
 *
 * @author Meine Toonen
 */
@Entity
public class LedAction implements Serializable {
    
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE)
    private int id;
    
    @Temporal(TemporalType.TIMESTAMP)
    private Date submitteddate;
    
    @Temporal(TemporalType.TIMESTAMP)
    private Date executeddate;
    
    private Boolean executed;
    
    private Boolean running;
    
    @Enumerated(EnumType.STRING)
    private CommandType command;
    
    private String commandparameters;
        
    public final static String SEPARATOR = ".|.";
    
    @Override
    public String toString() {
        return "LedAction{" + "command=" + command + ", commandparameters=" + commandparameters + '}';
    }
    
    public String toPacket(){
        StringBuilder sb = new StringBuilder();
        sb.append(SEPARATOR);
        sb.append(command.ordinal());
        sb.append(SEPARATOR);
        sb.append(commandparameters);
        sb.append(SEPARATOR);
        sb.append(id);
        sb.append(SEPARATOR);
        return sb.toString();
    }

    public String getCommandparameters() {
        return commandparameters;
    }

    public void setCommandparameters(String commandparameters) {
        this.commandparameters = commandparameters;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Date getSubmitteddate() {
        return submitteddate;
    }

    public void setSubmitteddate(Date submitteddate) {
        this.submitteddate = submitteddate;
    }

    public Date getExecuteddate() {
        return executeddate;
    }

    public void setExecuteddate(Date executeddate) {
        this.executeddate = executeddate;
    }

    public Boolean getExecuted() {
        return executed;
    }

    public void setExecuted(Boolean executed) {
        this.executed = executed;
    }

    public CommandType getCommand() {
        return command;
    }

    public void setCommand(CommandType command) {
        this.command = command;
    }

    public Boolean getRunning() {
        return running;
    }

    public void setRunning(Boolean running) {
        this.running = running;
    }

}
