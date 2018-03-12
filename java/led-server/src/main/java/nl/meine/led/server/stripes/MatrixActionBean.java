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
package nl.meine.led.server.stripes;

import javax.persistence.EntityManager;
import net.sourceforge.stripes.action.ActionBean;
import net.sourceforge.stripes.action.ActionBeanContext;
import net.sourceforge.stripes.action.DefaultHandler;
import net.sourceforge.stripes.action.ForwardResolution;
import net.sourceforge.stripes.action.Resolution;
import net.sourceforge.stripes.action.StreamingResolution;
import net.sourceforge.stripes.action.StrictBinding;
import net.sourceforge.stripes.action.UrlBinding;
import nl.meine.led.server.VarHolder;
import nl.meine.led.server.hibernate.CommandType;
import nl.meine.led.server.hibernate.LedAction;
import nl.meine.led.server.hibernate.Status;
import org.stripesstuff.stripersist.Stripersist;

/**
 *
 * @author Meine Toonen
 */
@StrictBinding
@UrlBinding(value = "/action/matrix/{$event}")
public class MatrixActionBean implements ActionBean{
    private ActionBeanContext context;
    
    private final String JSP = "/WEB-INF/jsp/matrix/view.jsp";

    public ActionBeanContext getContext() {
        return context;
    }

    public void setContext(ActionBeanContext context) {
        this.context = context;
    }
    
    @DefaultHandler
    public Resolution view(){
        EntityManager em = Stripersist.getEntityManager();
        Status s = new Status();
        s.setStatus("pietje");
        em.persist(s);
        em.getTransaction().commit();
        return new ForwardResolution(JSP);
    }
    
    public Resolution poll(){
        VarHolder instance = VarHolder.getInstance();
      /*  LedAction la = new LedAction();
        la.setCommand(instance.getCommand());
        la.setCommandparameters(instance.getParams());
        la.setId(12);
        */
        EntityManager em = Stripersist.getEntityManager();
        LedAction la = em.createQuery("from LedAction order by id DESC", LedAction.class).setMaxResults(1).getSingleResult();
        return new StreamingResolution("plain/text", la.toPacket()).setAttachment(true);
    }
    
    public Resolution status(){
        return new StreamingResolution("plain/text", "sadf");
    }
    
}

