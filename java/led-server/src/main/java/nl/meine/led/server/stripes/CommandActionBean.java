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
import net.sourceforge.stripes.action.Resolution;
import net.sourceforge.stripes.action.StreamingResolution;
import net.sourceforge.stripes.action.StrictBinding;
import net.sourceforge.stripes.action.UrlBinding;
import net.sourceforge.stripes.validation.EnumeratedTypeConverter;
import net.sourceforge.stripes.validation.Validate;
import net.sourceforge.stripes.validation.ValidateNestedProperties;
import nl.meine.led.server.hibernate.LedAction;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.stripesstuff.stripersist.EntityTypeConverter;
import org.stripesstuff.stripersist.Stripersist;

/**
 *
 * @author Meine Toonen
 */
@StrictBinding
@UrlBinding(value = "/action/command")
public class CommandActionBean  implements ActionBean{
    
    private final Log log = LogFactory.getLog(CommandActionBean.class);
    private final String JSP = "/WEB-INF/jsp/matrix/view.jsp";
    
    private ActionBeanContext context;
    
    @Validate(converter = EntityTypeConverter.class)
    @ValidateNestedProperties({
        @Validate(converter = EnumeratedTypeConverter.class, field = "command"),
        @Validate(field = "commandparameters")
    })
    private LedAction action;
    

    public Resolution add(){
        log.debug("Posting action... " + action.toString());
        EntityManager em = Stripersist.getEntityManager();
        em.persist(action);
        em.getTransaction().commit();
        return new StreamingResolution("plain/text", "asdfasdf");
    }
    
    public ActionBeanContext getContext() {
        return context;
    }

    public void setContext(ActionBeanContext context) {
        this.context = context;
    }

    public LedAction getAction() {
        return action;
    }

    public void setAction(LedAction action) {
        this.action = action;
    }
}
