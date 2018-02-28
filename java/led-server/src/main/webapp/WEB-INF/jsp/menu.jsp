<%--
Copyright (C) 2011-2013 B3Partners B.V.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@include file="/WEB-INF/jsp/taglibs.jsp"%>

<stripes:layout-definition>

    <!DOCTYPE html>
    <html class="x-border-box theme-triton">
        <head>
            <style>
                body {
                    padding-top:4rem;
                }
            </style>
            <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
            <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">

            <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
            <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
            <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>

            <stripes:layout-component name="head"/>

        </head>
        <body class="x-body">

            <%--div id="header">
                <div id="menu">
                    <ul>
                        <li class="menu-level1">
                            <a href="#">Gegevensregister</a>
                            <ul class="slideoutmenu">
                                <li><stripes:link beanclass="nl.meine.led.server.stripes.StatusActionBean" id="menu_attribuutbronnen">status</stripes:link></li>
                                <li>
                                    <a href="#" class="dropdownmenulink">Bronnen</a>
                                    <ul class="dropdownmenu">
                                        <li><stripes:link beanclass="nl.meine.led.server.stripes.StatusActionBean" id="menu_attribuutbronnen">status</stripes:link></li>
                                   </ul>
                                </li>
                            </ul>
                        </li>


                </ul>
            </div>
        </div--%>

            <nav class="navbar navbar-expand-md navbar-dark bg-dark fixed-top">
                <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarsExampleDefault" aria-controls="navbarsExampleDefault" aria-expanded="false" aria-label="Toggle navigation">
                    <span class="navbar-toggler-icon"></span>
                </button>

                <div class="collapse navbar-collapse" id="navbarsExampleDefault">
                    <ul class="navbar-nav mr-auto">
                        <li class="nav-item active">
                            <a class="nav-link" href="${contextPath}/index.jsp">Home <span class="sr-only">(current)</span></a>
                        </li>
                        <li class="nav-item">
                            <stripes:link class="nav-link" beanclass="nl.meine.led.server.stripes.StatusActionBean" id="menu_status">Status</stripes:link>
                            </li>
                            <li class="nav-item">
                            <stripes:link class="nav-link" beanclass="nl.meine.led.server.stripes.CommandActionBean" id="menu_status">Actie</stripes:link>
                            </li>
                            <!--li class="nav-item dropdown">
                                <a class="nav-link dropdown-toggle" href="http://example.com" id="dropdown01" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Dropdown</a>
                                <div class="dropdown-menu" aria-labelledby="dropdown01">
                                    <a class="dropdown-item" href="#">Action</a>
                                    <a class="dropdown-item" href="#">Another action</a>
                                    <a class="dropdown-item" href="#">Something else here</a>
                                </div>
                            </li-->
                        </ul>
                    </div>
                </nav>
                <main role="main" class="container">

                    <stripes:layout-component name="body"/>
            </main>
        </body>
    </html>

</stripes:layout-definition>
