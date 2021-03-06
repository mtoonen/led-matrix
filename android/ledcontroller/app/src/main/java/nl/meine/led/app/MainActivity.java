package nl.meine.led.app;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

public class MainActivity extends AppCompatActivity {
    public static final String EXTRA_MESSAGE = "nl.meine.led.app.MESSAGE";
    public static final String RESPONSE = "nl.meine.led.app.RESPONSE";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Spinner spinner = (Spinner) findViewById(R.id.commandType);
// Create an ArrayAdapter using the string array and a default spinner layout
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.commandTypeArray, android.R.layout.simple_spinner_item);
// Specify the layout to use when the list of choices appears
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
// Apply the adapter to the spinner
        spinner.setAdapter(adapter);

    }

    public void sendMessage(View v){
        EditText editText = (EditText) findViewById(R.id.editText);
        String message = editText.getText().toString();
        callLedServer(message);
    }

    public void callLedServer(String message){
        final Intent intent = new Intent(this, DisplayMessageActivity.class);
        intent.putExtra(EXTRA_MESSAGE, message);
//...

// Instantiate the RequestQueue.
        RequestQueue queue = Volley.newRequestQueue(this);
        //String url ="http://www.google.com";
        //http://localhost:8084/led-server/action/command?action.commandparameters=werwerwer&action.command=SHOW_TEXT&add=true
        String url = "https://led.meinetoonen.nl/led-server/action/command?action.command=SHOW_TEXT&add=true" +
                "&action.commandparameters=" +message;

// Request a string response from the provided URL.
        StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        // Display the first 500 characters of the response string.
                        String responseString = response;
                        intent.putExtra(RESPONSE, responseString);
                        startActivity(intent);
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                String responseString = "ERROR: " + error.getLocalizedMessage();
                intent.putExtra(RESPONSE, responseString);
                startActivity(intent);
            }
        });
// Add the request to the RequestQueue.
        queue.add(stringRequest);
    }
}
