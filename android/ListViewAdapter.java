package woong.memo;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;

/**
 * Created by Hyunwoo on 2015-12-10.
 */
public class ListViewAdapter extends BaseAdapter {
    private Context context = null;
    public ArrayList<ListData> listdata = new ArrayList<ListData>();
    public ListViewAdapter(Context con)
    {
        super();
        this.context = con;
    }

    @Override
    public int getCount()
    {
        return listdata.size();
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent)
    {
        if(convertView == null)
        {
            LayoutInflater flater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = flater.inflate(R.layout.listview_item, null);
            TextView text = (TextView)convertView.findViewById(R.id.Title);
            TextView date = (TextView)convertView.findViewById((R.id.Date));
            ListData data = listdata.get(position);
            text.setText(data.title);
            date.setText(data.date);
        }
        else {
            TextView text = (TextView)convertView.findViewById(R.id.Title);
            TextView date = (TextView)convertView.findViewById((R.id.Date));
            ListData data = listdata.get(position);
            text.setText(data.title);
            date.setText(data.date);
        }

        return convertView;
    }

    @Override
    public Object getItem(int position) {
        return listdata.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    public void addItem(int num, String t, String d, String c)
    {
        ListData add = null;
        add = new ListData();
        add.num = num;
        add.title = t;
        add.date = d;
        add.content = c;

        listdata.add(add);
    }

    public void remove(int position)
    {
        listdata.remove(position);

    }
}
