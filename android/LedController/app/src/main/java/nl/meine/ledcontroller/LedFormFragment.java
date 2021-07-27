package nl.meine.ledcontroller;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.JsonRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONException;
import org.json.JSONObject;

import nl.meine.ledcontroller.databinding.LedFormBinding;

public class LedFormFragment extends Fragment {

    private LedFormBinding binding;

    @Override
    public View onCreateView(
            LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState
    ) {

        binding = LedFormBinding.inflate(inflater, container, false);

        return binding.getRoot();

    }

    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        Spinner spinner = (Spinner) view.findViewById(R.id.messageType);
// Create an ArrayAdapter using the string array and a default spinner layout
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(getActivity().getBaseContext(),
                R.array.messageTypes, android.R.layout.simple_spinner_item);
// Specify the layout to use when the list of choices appears
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
// Apply the adapter to the spinner
        spinner.setAdapter(adapter);
        spinner.setSelection(0);
        binding.buttonFirst.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                try {

                    TextView tv = (TextView) binding.message;
                    callLedServer(tv.getText().toString());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                //NavHostFragment.findNavController(FirstFragment.this).navigate(R.id.action_FirstFragment_to_SecondFragment);
            }
        });
    }



    public void callLedServer(String message) throws JSONException {
        //  intent.putExtra(EXTRA_MESSAGE, message);
//...

// Instantiate the RequestQueue.
        RequestQueue queue = Volley.newRequestQueue(getActivity().getBaseContext());
        //String url ="http://www.google.com";
        //http://localhost:8084/led-server/action/command?action.commandparameters=werwerwer&action.command=SHOW_TEXT&add=true
        String url = "http://led.meinetoonen.nl:8080/led/messages/save";
        JSONObject b = new JSONObject();
        b.put("message",message);
        b.put("type","TEXT");
        b.put("PROCESSED",false);


// Request a string response from the provided URL.
        JsonRequest jsonRequest = new JsonObjectRequest(Request.Method.POST, url,b,
                new Response.Listener<JSONObject>() {
                    @Override
                    public void onResponse(JSONObject response) {
                        // Display the first 500 characters of the response string.
                        JSONObject responseString = response;
                        //       intent.putExtra(RESPONSE, responseString);
                        //      startActivity(intent);
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                String responseString = "ERROR: " + error.getLocalizedMessage();
                //   intent.putExtra(RESPONSE, responseString);
                // startActivity(intent);
            }
        });
// Add the request to the RequestQueue.
        queue.add(jsonRequest);
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }

}