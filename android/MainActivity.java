package woong.memo;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class MainActivity extends AppCompatActivity{
    public BroadcastReceiver mRegistrationBroadcastReceiver;

    public void getInstanceIdToken() {
        if (checkPlayServices()) {
            // Start IntentService to register this application with GCM.
            Intent intent = new Intent(this, MyGcmRegistrationService.class);
            startService(intent);
        }

        else
        {
            Intent intent = new Intent(this, MyGcmRegistrationService.class);
            startService(intent);
        }
    }

    public void regBroadcastReceiver(){
        mRegistrationBroadcastReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                String action = intent.getAction();

                //Toast.makeText(getApplicationContext(), "안녕하세요?", Toast.LENGTH_LONG).show();
            }
        };
    }

    public ListView listview;
    public static ListViewAdapter adapter;
    public LoadContents load;
    Intent i;

    String ID;
    public static ListViewAdapter getAdapter()
    {
        return adapter;
    }

    @Override
    protected void onResume() {
        super.onResume();
        adapter.notifyDataSetInvalidated();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        i = getIntent();
        ID = i.getStringExtra("ID");
        Toast.makeText(getApplicationContext(), ID, Toast.LENGTH_SHORT).show();

        listview = (ListView) findViewById(R.id.List);
        adapter = new ListViewAdapter(this);
        listview.setAdapter(adapter);

        load = new LoadContents(ID);
        load.execute();

        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> parent, View v, int position, long id) {
                ListData d = adapter.listdata.get(position);
                Toast.makeText(MainActivity.this, d.title, Toast.LENGTH_SHORT).show();
                Intent i = new Intent(MainActivity.this, ContentActivity.class);
                i.putExtra("num", d.num);
                i.putExtra("position", position);
                i.putExtra("title", d.title);
                i.putExtra("content", d.content);
                i.putExtra("ID", ID);
                startActivity(i);

            }
        });

        regBroadcastReceiver();
        getInstanceIdToken();
        //Log.d("adatper", adapter.getItem(0).toString());
        //adapter.notify();
        //send = new SendGCM();
        //send.execute();

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent i = new Intent(MainActivity.this, ContentActivity.class);
                i.putExtra("new", 1);
                i.putExtra("ID", ID);
                startActivity(i);
            }
        });
    }

    public class LoadContents extends AsyncTask<Void, Void, Boolean> {

        String mID;

        LoadContents(String ID)
        {
            this.mID = ID;
        }

        @Override
        protected Boolean doInBackground(Void... params) {
            // TODO: attempt authentication against a network service.

            try {
                URL url = new URL("http://54.201.117.101/memo/content.php?id=" + mID);
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();

                connection.setDefaultUseCaches(false);
                connection.setDoInput(true);
                connection.setDoOutput(true);
                connection.setRequestMethod("POST");
                connection.setConnectTimeout(10000);
                connection.setReadTimeout(10000);
                connection.setRequestProperty("Accept", "application/json");
                connection.setRequestProperty("Content-Type", "application/json; charset=UTF-8");
                connection.setRequestProperty("Cache-Control", "no-cache");

                int responseCode = connection.getResponseCode();
                if (responseCode == HttpURLConnection.HTTP_OK) {
                    InputStream is = connection.getInputStream();
                    ByteArrayOutputStream baos = new ByteArrayOutputStream();

                    byte[] byteBuffer = new byte[1024];
                    byte[] byteData = null;
                    int nLength = 0;

                    while ((nLength = is.read(byteBuffer, 0, byteBuffer.length)) != -1)
                        baos.write(byteBuffer, 0, nLength);

                    byteData = baos.toByteArray();

                    String response = new String(byteData);
                    try
                    {
                        JSONArray JArr = new JSONArray(response);
                        int length = JArr.length();
                        for (int i = 0; i < length; i++)
                        {
                            JSONObject JObject = JArr.getJSONObject(i);
                            int num = JObject.getInt("num");
                            String date = JObject.getString("date");
                            String title = JObject.getString("title");
                            String content = JObject.getString("content");

                            adapter.addItem(num, title, date, content);
                        }
                    }

                    catch (JSONException e)
                    {
                        e.printStackTrace();
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
                return false;
            }

            return true;
        }

        @Override
        protected void onPostExecute(Boolean success) {
            adapter.notifyDataSetInvalidated();
        }
    }

    /*private class ViewHolder
    {
        public TextView text;
    }*/

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            SharedPreferences setting;
            setting = getSharedPreferences("setting", 0);
            SharedPreferences.Editor editor;
            editor = setting.edit();
            editor.remove("id");
            editor.apply();

            Intent i = new Intent(MainActivity.this, LoginActivity.class);
            startActivity(i);
            finish();
        }

        return super.onOptionsItemSelected(item);
    }

    private boolean checkPlayServices() {
        int resultCode = GooglePlayServicesUtil.isGooglePlayServicesAvailable(this);
        if (resultCode != ConnectionResult.SUCCESS) {
            if (GooglePlayServicesUtil.isUserRecoverableError(resultCode)) {
                GooglePlayServicesUtil.getErrorDialog(resultCode, this,
                        9000).show();
            } else {
                Log.i("NO SUPPORT", "This device is not supported.");
                finish();
            }
            return false;
        }
        return true;
    }
}
