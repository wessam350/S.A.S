package com.example.a499;

import android.content.Intent;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class Get_Data extends AppCompatActivity {

    private DatabaseReference reference;
    private FirebaseAuth auth;

    private TextView textView;
    private Button ok;
    private EditText textuser;
    private EditText num;
    private Button bck;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_get__data);

        auth = FirebaseAuth.getInstance();
//        final FirebaseUser user = auth.getCurrentUser();

        textView = (TextView) findViewById(R.id.test);
        ok = (Button) findViewById(R.id.OK);
        textuser =(EditText)findViewById(R.id.textuser);
        bck = (Button)findViewById(R.id.Back);
        bck.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                BACK();
            }
        });
        textView.setText("welcome");


        ok.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
//                String dd = textView.getText().toString();
//                if (dd.equals("")){
//                    Intent inten = new Intent(Get_Data.this, ProfileActivity.class);
//                    startActivity(inten);
//                    Toast.makeText(Get_Data.this, "The number should be write ", Toast.LENGTH_SHORT).show();
////                            Intent intent = new Intent(Get_Data.this, ProfileActivity.class);
////                            startActivity(intent);
//                }

                    okk();


            }
        });

    }

    private void okk(){
        reference = FirebaseDatabase.getInstance().getReference().child("Users");
//                reference = FirebaseDatabase.getInstance().getReference().child("Users").child("NumOfTag");

        reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                FirebaseUser user = auth.getCurrentUser();
                String usertx = textuser.getText().toString();
                String h =  dataSnapshot.child("NumOfTag").getValue().toString();

                int g = Integer.parseInt(h);
                for (int i = 1; i<=g; i++) {
                    String name = dataSnapshot.child("tag"+ i).getValue().toString();

                    if (name.equals(usertx)) {
                        reference = FirebaseDatabase.getInstance().getReference();
                        reference.child(user.getUid()).child("tag"+i).setValue(name);
                        reference.child("Users").child("tag"+i).setValue("***");
                        if (!usertx.equals("")){
                        Intent intent = new Intent(Get_Data.this, Show_Tags.class);
                        startActivity(intent);
                        }

                    }
                    else{
                        if (i == g) {

                            Toast.makeText(Get_Data.this, "Error we don't found the tag", Toast.LENGTH_SHORT).show();
                        }
                    }
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });
    }

    private void BACK() {
        Intent inte = new Intent(this, ProfileActivity.class);
        startActivity(inte);

    }
}
