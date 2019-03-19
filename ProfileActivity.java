package com.example.a499;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class ProfileActivity extends AppCompatActivity implements View.OnClickListener {

    private FirebaseAuth firebaseAuth;

    private TextView textviewuseremil;
    private Button blogout;

    private DatabaseReference databaseReference;
//
//    private EditText editTextname;
//    private EditText editTextaddres ;
    private Button button2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);

        firebaseAuth = firebaseAuth.getInstance();

        if (firebaseAuth.getCurrentUser() == null){
            finish();
            startActivity(new Intent(this,loginpage.class));
        }

        databaseReference = FirebaseDatabase.getInstance().getReference();
//        editTextname = (EditText)findViewById(R.id.editTextname);
//        editTextaddres = (EditText)findViewById(R.id.editTextaddres);
        button2 =(Button) findViewById(R.id.button2);

        FirebaseUser user = firebaseAuth.getCurrentUser();

//        textviewuseremil = (TextView)findViewById(R.id.textviewuseremil);

//        textviewuseremil.setText(user.getEmail());

        blogout = (Button) findViewById(R.id.blogout);


        blogout.setOnClickListener(this);
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                saveinfo();
            }
        });
    }
        private void saveinfo(){

//        String name = editTextname.getText().toString().trim();
//            String add = editTextaddres.getText().toString().trim();
//
//            userinfo objinfo = new userinfo(name,add);
//            firebaseAuth = firebaseAuth.getInstance();
//
//            FirebaseUser user = firebaseAuth.getCurrentUser();
//            databaseReference.child(user.getUid()).setValue(objinfo);
//            Toast.makeText(this,"info saved " ,Toast.LENGTH_LONG).show();

            Intent intent = new Intent(this, Get_Data.class);
            startActivity(intent);
        }
    @Override
    public void onClick(View v) {
if (v == blogout){
    firebaseAuth.signOut();
    finish();
    startActivity(new Intent(this ,loginpage.class));
}

if (v == button2){

    saveinfo();
}

    }
}
