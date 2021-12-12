//
//  ContentView.swift
//  Pet_Feeder
//
//  Created by 韩丽颖 on 2021/11/7.
//

import SwiftUI

struct GrowingButton: ButtonStyle {
    func makeBody(configuration: Configuration) -> some View {
        configuration.label
            .frame(width: 100, height: 100)
            .background(Color.blue)
            .foregroundColor(.white)
            .clipShape(Circle())
            .scaleEffect(configuration.isPressed ? 1.2 : 1)
            .animation(.easeOut(duration: 0.2), value: configuration.isPressed)
            .padding(100)
        
    }
}

struct Feed: Codable {
    var bowlAmount: Int = 0
    var failType: String = ""
    var isSuccess: Bool = false
    var tankRemain: Int = 0
}

struct ContentView: View {
    var feed = Feed()
    @State private var confirmationMessage = ""
    @State private var showingConfirmation = false
    @State private var successTitle = ""
    @ObservedObject var food = Food()
    
    var body: some View {
        NavigationView {
            VStack() {
                HStack {
                    Button("Feed") {
                        print("feeded")
                        self.getStatus()
                    }.buttonStyle(GrowingButton())
                    
                }
                List {
                    NavigationLink(destination: SettingView(food: food)) {
                        Text("Settings")
                    }
                    
                    NavigationLink(destination: ActivityView()) {
                        Text("Activity History")
                    }
                }
                
            }.navigationBarHidden(true)
        }.alert(isPresented: $showingConfirmation) {
            Alert(title: Text(successTitle), message: Text(confirmationMessage), dismissButton: .default(Text("OK")))
        }
        
        
    }
    
    func getStatus() {
        guard let encoded = try? JSONEncoder().encode(feed) else {
            print("Failed to encode")
            return
        }
        
        let url = URL(string: "http://172.91.84.234:5000/feed")!
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
                if decodedFeed.isSuccess {
                    print("success")
                    self.successTitle = "Succeed!"
                    self.confirmationMessage = "The food in the bowl is \(decodedFeed.bowlAmount)g, and the remaing amount in the tank is \(decodedFeed.tankRemain)%."
                } else {
                    self.successTitle = "Fail!"
                    self.confirmationMessage = "Reason: \(decodedFeed.failType)."
                }
                
                self.showingConfirmation = true
            } else {
                print("Invalid response from server")
            }
        }.resume()
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        Group {
            ContentView()
                
            ContentView()
        }
    }
}
