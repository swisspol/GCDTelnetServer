/*
 Copyright (c) 2012-2014, Pierre-Olivier Latour
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * The name of Pierre-Olivier Latour may not be used to endorse
 or promote products derived from this software without specific
 prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL PIERRE-OLIVIER LATOUR BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "GCDNetworking.h"

@interface GCDTelnetConnection : GCDTCPServerConnection
@property(nonatomic, readonly) NSString* terminalType;
@property(nonatomic, readonly, getter=isColorTerminal) BOOL colorTerminal;
@property(nonatomic, copy) NSString* prompt;  // Default is "> " (behavior is undefined if changed outside of start handler - must be ASCII)
@property(nonatomic, copy) NSString* tabPlaceholder;  // Default is "\t" (behavior is undefined if changed outside of start handler - must be ASCII)
@property(nonatomic) NSUInteger maxHistorySize;  // Set to 0 to disable history - Default is unlimited (behavior is undefined if changed outside of start handler)
- (BOOL)writeANSIString:(NSString *)string withTimeout:(NSTimeInterval)timeout;
- (void)writeANSIStringAsynchronously:(NSString*)string completion:(void (^)(BOOL success))completion;
@end

@interface GCDTelnetConnection (Subclassing)
@property(nonatomic, readonly) NSMutableString* lineBuffer;  // ASCII characters only

- (NSData*)processCursorUp;
- (NSData*)processCursorDown;
- (NSData*)processCursorForward;
- (NSData*)processCursorBack;
- (NSData*)processOtherANSIEscapeSequence:(NSData*)data;

- (NSData*)processTab;
- (NSData*)processDelete;
- (NSData*)processCarriageReturn;
- (NSData*)processOtherASCIICharacter:(unsigned char)character;

- (NSData*)processOtherData:(NSData*)data;

- (NSData*)processRawInput:(NSData*)data;

- (NSString*)processLine:(NSString*)line;
@end
