/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package nl.meine.led.server.stripes;

import java.util.List;
import javax.persistence.EntityManager;
import net.sourceforge.stripes.action.ActionBean;
import net.sourceforge.stripes.action.ActionBeanContext;
import net.sourceforge.stripes.action.DefaultHandler;
import net.sourceforge.stripes.action.ForwardResolution;
import net.sourceforge.stripes.action.Resolution;
import net.sourceforge.stripes.action.StrictBinding;
import net.sourceforge.stripes.action.UrlBinding;
import nl.meine.led.server.hibernate.LedAction;
import org.stripesstuff.stripersist.Stripersist;

/**
 *
 * @author Meine Toonen
 */
@StrictBinding
@UrlBinding(value = "/action/status")
public class StatusActionBean implements ActionBean{
    private ActionBeanContext context;
    
    private final String JSP = "/WEB-INF/jsp/status/view.jsp";
    
    private LedAction current;
    
    private List<LedAction> actions;

    // <editor-fold desc="getters and setters" defaultstate="collapsed">
    public LedAction getCurrent() {
        return current;
    }

    public void setCurrent(LedAction current) {
        this.current = current;
    }

    public List<LedAction> getActions() {
        return actions;
    }

    public void setActions(List<LedAction> actions) {
        this.actions = actions;
    }

    public ActionBeanContext getContext() {
        return context;
    }

    public void setContext(ActionBeanContext context) {
        this.context = context;
    }
    // </editor-fold>
    
    @DefaultHandler
    public Resolution view(){
        EntityManager em  = Stripersist.getEntityManager();
        
        current = em.createQuery("FROM LedAction WHERE running = true", LedAction.class).getSingleResult();
        actions = em.createQuery("FROM LedAction", LedAction.class).getResultList();
        return new ForwardResolution(JSP);
    }
}
