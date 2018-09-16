package woong.memo;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;

import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class ContentActivity extends AppCompatActivity {

    Intent i = null;
    ModifyContent in;
    InsertContent ins;
    ListData printData;
    EditText title;
    EditText content;

    String initTitle;
    String initContent = null;

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        switch (keyCode)
        {
            case KeyEvent.KEYCODE_BACK:
            {
                i = getIntent();
                final int id = i.getIntExtra("num", -1);
                final int insert = i.getIntExtra("new", 0);
                String postTitle = title.getText().toString();
                String postContent = content.getText().toString();

                if(insert == 0) {
                    if (postTitle.equals(initTitle) && postContent.equals(initContent))
                        return super.onKeyDown(keyCode, event);

                    in = new ModifyContent(id, postTitle, postContent); // title, content
                    in.execute();
                }
                else if (insert == 1)
                {
                    if (initTitle == null)
                        return super.onKeyDown(keyCode, event);

                    String ID = i.getStringExtra("ID");
                    ins = new InsertContent(ID, postTitle, postContent);
                    ins.execute();
                }
            }
        }

        return super.onKeyDown(keyCode, event);
    }

    public class ModifyContent extends AsyncTask<Void, Void, Boolean> {

        int mNum;
        String mTitle;
        String mContent;

        ModifyContent(int num, String title, String content)
        {
            this.mNum = num;
            this.mTitle = title;
            this.mContent = content;
        }

        @Override
        protected Boolean doInBackground(Void... params) {
            // TODO: attempt authentication against a network service.

            try {
                String mContentEncoded = new String(mContent.getBytes("utf-8"));
                String urlString = "http://54.201.117.101/memo/modify.php?num=" + mNum + "&title=" + mTitle + "&content=" + mContent;
                urlString = urlString.replace(" ", "+");
                URL url = new URL(urlString);
                // +는 금지 단어다.
                Log.d("URL", urlString);
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

                if (connection.getResponseCode() == HttpURLConnection.HTTP_OK) {
                    InputStream is = connection.getInputStream();
                    ByteArrayOutputStream baos = new ByteArrayOutputStream();

                    byte[] byteBuffer = new byte[1024];
                    byte[] byteData = null;
                    int nLength = 0;

                    while ((nLength = is.read(byteBuffer, 0, byteBuffer.length)) != -1)
                        baos.write(byteBuffer, 0, nLength);

                    byteData = baos.toByteArray();

                    String response = new String(byteData);
                    JSONObject responseJSON = new JSONObject(response);
                    int result = Integer.parseInt((String) responseJSON.get("result"));

                    if (result == 1)
                        return true;

                    else
                        return false;

                }
            } catch (Exception e) {
                e.printStackTrace();
                return false;
            }

            return true;
        }

        @Override
        protected void onPostExecute(Boolean success) {
            if (success)
            {
                i = getIntent();
                int position = i.getIntExtra("position", -1);
                ListData li = new ListData();
                li.num = mNum;
                li.content = mContent;
                li.title = mTitle;
                Calendar c = Calendar.getInstance();
                SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd");
                li.date = df.format(c.getTime());

                MainActivity.adapter.listdata.set(position, li);
                MainActivity.adapter.notifyDataSetChanged();
                Toast.makeText(getApplicationContext(), "변경된 내용이 잘 저장됐습니다.", Toast.LENGTH_SHORT).show();

            }

            else
                Toast.makeText(getApplicationContext(), "변경 내용 저장 실패.", Toast.LENGTH_SHORT).show();
        }
    }

    public class InsertContent extends AsyncTask<Void, Void, Boolean> {

        String mID;
        String mTitle;
        String mContent;
        int num;

        InsertContent(String id, String title, String content)
        {
            this.mID = id;
            this.mTitle = title;
            this.mContent = content;
        }

        @Override
        protected Boolean doInBackground(Void... params) {
            // TODO: attempt authentication against a network service.

            try {
                String urlString = "http://54.201.117.101/memo/insert.php?id=" + mID + "&title=" + mTitle + "&content=" + mContent;
                urlString = urlString.replace(" ", "+");
                URL url = new URL(urlString);
                // +는 금지 단어다.
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

                if (connection.getResponseCode() == HttpURLConnection.HTTP_OK) {
                    InputStream is = connection.getInputStream();
                    ByteArrayOutputStream baos = new ByteArrayOutputStream();

                    byte[] byteBuffer = new byte[1024];
                    byte[] byteData = null;
                    int nLength = 0;

                    while ((nLength = is.read(byteBuffer, 0, byteBuffer.length)) != -1)
                        baos.write(byteBuffer, 0, nLength);

                    byteData = baos.toByteArray();

                    String response = new String(byteData);
                    JSONObject responseJSON = new JSONObject(response);
                    int result = Integer.parseInt((String) responseJSON.get("result"));
                    num = Integer.parseInt((String) responseJSON.get("num"));

                    if (result == 1)
                        return true;

                    else
                        return false;

                }
            } catch (Exception e) {
                e.printStackTrace();
                return false;
            }

            return true;
        }

        @Override
        protected void onPostExecute(Boolean success) {
            if (success)
            {
                Calendar c = Calendar.getInstance();
                SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd");

                MainActivity.adapter.addItem(num, title.getText().toString(), df.format(c.getTime()), content.getText().toString());
                MainActivity.adapter.notifyDataSetChanged();
                Toast.makeText(getApplicationContext(), "변경된 내용이 잘 저장됐습니다.", Toast.LENGTH_SHORT).show();

            }

            else
                Toast.makeText(getApplicationContext(), "변경 내용 저장 실패.", Toast.LENGTH_SHORT).show();
        }
    }

    public class DeleteContent extends AsyncTask<Void, Void, Boolean> {

        int num;

        DeleteContent(int n)
        {
            this.num = n;
        }

        @Override
        protected Boolean doInBackground(Void... params) {
            // TODO: attempt authentication against a network service.

            try {
                String urlString = "http://54.201.117.101/memo/delete.php?num=" + num;
                URL url = new URL(urlString);
                // +는 금지 단어다.
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

                if (connection.getResponseCode() == HttpURLConnection.HTTP_OK) {
                    InputStream is = connection.getInputStream();
                    ByteArrayOutputStream baos = new ByteArrayOutputStream();

                    byte[] byteBuffer = new byte[1024];
                    byte[] byteData = null;
                    int nLength = 0;

                    while ((nLength = is.read(byteBuffer, 0, byteBuffer.length)) != -1)
                        baos.write(byteBuffer, 0, nLength);

                    byteData = baos.toByteArray();

                    String response = new String(byteData);
                    JSONObject responseJSON = new JSONObject(response);
                    int result = Integer.parseInt((String) responseJSON.get("result"));

                    if (result == 1)
                        return true;

                    else
                        return false;

                }
            } catch (Exception e) {
                e.printStackTrace();
                return false;
            }

            return true;
        }

        @Override
        protected void onPostExecute(Boolean success) {
            if (success)
            {
                i = getIntent();
                int position = i.getIntExtra("position", -1);
                MainActivity.adapter.listdata.remove(position);
                MainActivity.adapter.notifyDataSetChanged();
                Toast.makeText(getApplicationContext(), "변경된 내용이 잘 저장됐습니다.", Toast.LENGTH_SHORT).show();

            }

            else
                Toast.makeText(getApplicationContext(), "변경 내용 저장 실패.", Toast.LENGTH_SHORT).show();
        }
    }

    ImageButton btn;
    int insert;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_content);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        i = getIntent();
        insert = i.getIntExtra("new", 0);

        btn = (ImageButton)findViewById(R.id.Delete_Button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                i = getIntent();
                if (insert == 1)
                    finish();

                 int num = i.getIntExtra("num", -1);
                 int postion = i.getIntExtra("pos", -1);
                DeleteContent dc;
                dc = new DeleteContent(num);
                dc.execute();
                finish();
            }
        });

        title = (EditText) findViewById(R.id.memo_title);
        content = (EditText) findViewById(R.id.memo_content);
        title.setText("");
        content.setText("");
        initContent = content.getText().toString();
        initTitle = title.getText().toString();

        if (insert == 0) {
            printData = new ListData();
            printData.title = i.getStringExtra("title");
            printData.content = i.getStringExtra("content");

            title.setText(printData.title);
            content.setText(printData.content);
        }
    }

}
