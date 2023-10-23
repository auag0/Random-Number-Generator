package com.anago.randomnumber

import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.activity.viewModels
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    private val viewModel: MainViewModel by viewModels()
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val randomNumberText: TextView = findViewById(R.id.text_random_number)
        val generateBtn: Button = findViewById(R.id.btn_generate)

        generateBtn.setOnClickListener {
            viewModel.generateRandomNumber()
        }

        viewModel.randomNumber.observe(this) {
            randomNumberText.text = "$it"
        }
    }
}