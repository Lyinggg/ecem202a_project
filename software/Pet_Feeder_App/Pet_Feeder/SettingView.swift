//
//  SettingView.swift
//  Pet_Feeder
//
//  Created by 韩丽颖 on 2021/11/7.
//

import SwiftUI

struct SettingView: View {
    @ObservedObject var food: Food
    var setFre: Int = 6
    var setAmount: Int = 20
    
    var body: some View {
        Form {
            Section {
                Stepper(value: $food.frequency, in: 3...20) {
                    Text("Feed interval (hours): \(food.frequency)")
                }
            }
            
            Section {
                Picker("Feed amount each time (grams)", selection: $food.amount) {
                    ForEach(0..<food.amount_list.count) {
                        Text("\(food.amount_list[$0])")
                    }
                }
            }
        }.navigationTitle("Auto-Feeding")
        Button("Set") {
            print("set")
            self.setF()
            self.setA()
        }.buttonStyle(GrowingButton())
    }
    
    func setF() {
        guard let encoded = try? JSONEncoder().encode(setFre) else {
            print("Failed to encode")
            return
        }
        
        let url = URL(string: "http://172.91.84.234:5000/setFre")!
        var request = URLRequest(url: url)
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.httpMethod = "POST"
        request.httpBody = encoded
        
        URLSession.shared.dataTask(with: request) { data, response, error in
            // handle the result here.
            guard let data = data else {
                print("No data in response: \(error?.localizedDescription ?? "Unknown error").")
                return
            }
            
            let str = String(decoding: data, as: UTF8.self)
            print(str)
            
            if let decodedFeed = try? JSONDecoder().decode(Feed.self, from: data) {
                print(decodedFeed)
            }
        }.resume()
    }
    
    func setA() {
        guard let encoded = try? JSONEncoder().encode(setAmount) else {
            print("Failed to encode")
            return
        }
        
        let url = URL(string: "http://172.91.84.234:5000/setAmount")!
        var request = URLRequest(url: url)
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.httpMethod = "POST"
        request.httpBody = encoded
        
        URLSession.shared.dataTask(with: request) { data, response, error in
            // handle the result here.
            guard let data = data else {
                print("No data in response: \(error?.localizedDescription ?? "Unknown error").")
                return
            }
            
            let str = String(decoding: data, as: UTF8.self)
            print(str)
            
            if let decodedFeed = try? JSONDecoder().decode(Feed.self, from: data) {
                print(decodedFeed)
            }
        }.resume()
    }
}

struct SettingView_Previews: PreviewProvider {
    static var previews: some View {
        SettingView(food: Food())
    }
}
